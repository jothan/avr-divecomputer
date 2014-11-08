#include <assert.h>
#include <string.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_spi.h>
#include "diag/Trace.h"

#include "depth.h"
#include "main.h"
#include "pins.h"
#include "types.h"

static const u8 CMD_RESET = 0x1e;
static const u8 CMD_READ_PROM = 0xa0;
static const u8 CMD_SAMPLE_PRESSURE = 0x40;
static const u8 CMD_SAMPLE_TEMPERATURE = 0x50;
static const u8 CMD_READ_ADC = 0x00;
static const u32 TIMEOUT = 100; // ms
static const i32 PRESSURE_MIN = 0;
static const i32 PRESSURE_MAX = 600000; // mbar * 100
static const i32 TEMPERATURE_MIN = -4000; // C * 100
static const i32 TEMPERATURE_MAX = 8500; // C * 100

// From Meas-Spec AN520 note.
static 	u8 CRC_TEST_VECTOR[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40,0x41, 0x42, 0x43, 0x44,0x45, 0x0b};

static inline u16 prom_to_u16(const u8 *prom, size_t idx)
{
	const u8 *val = &prom[idx*2];
	return val[0] << 8 | val[1];
}


struct sampling_type_t {
	u32 delay_us;
	u8 cmd;
};

static const sampling_type_t SAMPLING_TYPE[] = {
		{ 600, 0x00}, // OSR =  256
		{1170, 0x02}, // OSR =  512
		{2280, 0x04}, // OSR = 1024
		{4540, 0x06}, // OSR = 2048
		{9040, 0x08}, // OSR = 4096
};

DepthSensor::DepthSensor()
{
	spi.Instance = DEPTH_SPI;
	spi.Init.Mode = SPI_MODE_MASTER;
	spi.Init.Direction = SPI_DIRECTION_2LINES;
	spi.Init.DataSize = SPI_DATASIZE_8BIT;
	spi.Init.CLKPolarity = SPI_POLARITY_LOW;
	spi.Init.CLKPhase = SPI_PHASE_1EDGE;
	spi.Init.NSS = SPI_NSS_SOFT;
	spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	spi.Init.FirstBit = SPI_FIRSTBIT_MSB;
	spi.Init.TIMode = SPI_TIMODE_DISABLED;
	spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
	spi.Init.CRCPolynomial = 0xffff;
}

inline void DepthSensor::cs(bool sel)
{
	HAL_GPIO_WritePin(DEPTH_CS_PIN.port, DEPTH_CS_PIN.number, sel ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void DepthSensor::reset(void)
{
	u8 cmd = CMD_RESET;

	cs(true);

	HAL_SPI_Transmit(&spi, &cmd, 1, TIMEOUT);
	HAL_Delay(3);

	cs(false);
}

void DepthSensor::read_prom(void)
{
	u8 cmd[3] = {};
	u8 recv[3];

	for(int i = 0; i < 8; i++) {
		cs(true);
		cmd[0] = CMD_READ_PROM + i*2;
		HAL_SPI_TransmitReceive(&spi, cmd, recv, 3, TIMEOUT);
		memcpy(&prom[i*2], &recv[1], 2);
		cs(false);
	}


	for(int i = 0; i < 8; i++) {
		u16 factor = ((u16)(prom[i*2]) << 8) + prom[i*2+1];
		trace_printf("%d: 0x%04x %d\n", i, factor, factor);
	}
	assert(crc4(prom, sizeof(prom)) == 0);
}

void DepthSensor::enable(void)
{
	DEPTH_SPI_ENABLE();
	HAL_SPI_Init(&spi);
	pin_enable();

	reset();
	read_prom();
}

void DepthSensor::disable(void)
{
	pin_disable();
	DEPTH_SPI_DISABLE();
}

void DepthSensor::pin_enable(void)
{
	GPIO_InitTypeDef gpio;

	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_LOW;
	gpio.Alternate = DEPTH_SPI_AF;

	// MOSI
	gpio.Pin = DEPTH_MOSI_PIN.number;
	HAL_GPIO_Init(DEPTH_MOSI_PIN.port, &gpio);

	// SCK
	gpio.Pin = DEPTH_SCK_PIN.number;
	HAL_GPIO_Init(DEPTH_SCK_PIN.port, &gpio);

	// MISO
	gpio.Pin = DEPTH_MISO_PIN.number;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(DEPTH_MISO_PIN.port, &gpio);

	// CS
	gpio.Pin = DEPTH_CS_PIN.number;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Alternate = 0;
	HAL_GPIO_Init(DEPTH_CS_PIN.port, &gpio);
}

void DepthSensor::pin_disable(void)
{
	HAL_GPIO_DeInit(DEPTH_MOSI_PIN.port, DEPTH_MOSI_PIN.number);
	HAL_GPIO_DeInit(DEPTH_SCK_PIN.port, DEPTH_SCK_PIN.number);
	HAL_GPIO_DeInit(DEPTH_MISO_PIN.port, DEPTH_MISO_PIN.number);
	HAL_GPIO_DeInit(DEPTH_CS_PIN.port, DEPTH_CS_PIN.number);
}

inline u32 DepthSensor::sample(u8 cmd, DepthSampling osr)
{
	u8 cmd_buf[4] = {};
	u8 recv[4];
	assert(osr >= DepthSampling::OSR_256 && osr <= DepthSampling::OSR_4096);
	assert(cmd == CMD_SAMPLE_PRESSURE || cmd == CMD_SAMPLE_TEMPERATURE);

	const sampling_type_t &sampling = SAMPLING_TYPE[osr];

	cmd_buf[0] = cmd | sampling.cmd;
	cs(true);
	HAL_SPI_Transmit(&spi, cmd_buf, 1, TIMEOUT);
	cs(false);

	HAL_Delay(sampling.delay_us / 1000 + 1);

	cmd_buf[0] = CMD_READ_ADC;

	cs(true);
	HAL_SPI_TransmitReceive(&spi, cmd_buf, recv, 4, TIMEOUT);
	cs(false);

	return recv[1] << 16 | recv[2] << 8 | recv[3];
}

u32 DepthSensor::sample_temperature(DepthSampling osr)
{
	return sample(CMD_SAMPLE_TEMPERATURE, osr);
}

u32 DepthSensor::sample_pressure(DepthSampling osr)
{
	return sample(CMD_SAMPLE_PRESSURE, osr);
}

/*
 * Compute CRC-4 over the whole PROM block, returns 0 on success.
 */
u8 DepthSensor::crc4(const u8 *data, size_t size)
{
	u16 rem = 0;

	for(uint i=0; i < size; i++) {
		rem ^= i != size - 1 ? data[i] : data[i] << 4;

		for(int b=8; b > 0; b--)
			rem = rem & 0x8000 ? (rem << 1) ^ 0x3000 : rem << 1;
	}

	return rem >> 12;
}

void DepthSensor::convert_values(u32 pressure_in, u32 temperature_in, i32 &pressure_out, i32 &temperature_out)
{
	u16 sens_t1 = prom_to_u16(prom, 1);
	u16 off_t1 = prom_to_u16(prom, 2);
	u16 tcs = prom_to_u16(prom, 3);
	u16 tco = prom_to_u16(prom, 4);
	u16 t_ref = prom_to_u16(prom, 5);
	u16 tempsens = prom_to_u16(prom, 6);

	i32 dt = temperature_in - (t_ref << 8);
	i32 temp = 2000 + ((i64)dt * tempsens >> 23);

	i32 t2;
	i64 off2, sens2;
	if(temp < 2000) {
		t2 = 3 * (i64)dt * dt >> 33;
		i64 temp_squared = ((i64)temp - 2000) * ((i64)temp - 2000);
		off2 = 3 * temp_squared >> 3;
		sens2 = 7 * temp_squared >> 3;
		if(temp < -1500)
			sens2 += 3 * ((i64)temp + 1500) * ((i64)temp + 1500);
	} else {
		t2 = 0;
		off2 = 0;
		sens2 = 0;
	}
	temperature_out = temp - t2;

	i64 off = ((i64)off_t1 << 18) + ((i64)tco * dt >> 5) - off2;
	i64 sens = ((i64)sens_t1 << 17) + ((i64)tcs * dt >> 7) - sens2;
	pressure_out = ((((i64)pressure_in * sens) >> 21) - off) >> 15;

	assert(temperature_out >= TEMPERATURE_MIN && temperature_out <= TEMPERATURE_MAX);
	assert(pressure_out >= PRESSURE_MIN && pressure_out <= PRESSURE_MAX);

	trace_printf("%4d.%02d mbar, %d.%02d C\n", pressure_out / 100, pressure_out % 100, temperature_out / 100, (temperature_out > 0 ? temperature_out : -temperature_out) % 100);
}


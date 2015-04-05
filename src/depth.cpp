/*
 * Driver for the MS5803-05BA pressure and temperature sensor.
 */

#include <assert.h>
#include <string.h>
#include <math.h>
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_spi.h>
#include <cortexm/ExceptionHandlers.h>
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
static const u32 RESET_DELAY = 3; // ms
static const i32 PRESSURE_MIN = 0;
static const i32 PRESSURE_MAX = 600000; // mbar * 100
static const i32 TEMPERATURE_MIN = -4000; // C * 100
static const i32 TEMPERATURE_MAX = 8500; // C * 100


PressureSensor depth;

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

PressureSensor::PressureSensor()
	:raw_pressure(0), raw_temperature(0), last_pressure(NAN), last_temperature(NAN)
{
	timer.callback = PressureSensor::callback_timer;
	timer.arg = this;
	state = UNINIT;
}

PressureSensor::~PressureSensor()
{
	main_timer.cancel(&timer);
	disable();
}

void PressureSensor::callback_timer(void *arg)
{
	PressureSensor &sensor = *(PressureSensor*)arg;

	switch(sensor.state)
	{
	case WAIT_RESET:
		sensor.callback_reset_wait();
		break;
	case WAIT_SAMPLE_ADC:
		sensor.callback_sample_sampled();
		break;
	default:
		assert(0);
	}
}

inline void PressureSensor::cs(bool sel)
{
	HAL_GPIO_WritePin(DEPTH_CS_PIN.port, DEPTH_CS_PIN.number, sel ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void PressureSensor::reset(void)
{
	cs(true);

	dma_tx_buf[0] = CMD_RESET;
	// DMA does not like transferring a single outbound byte for some reason.
	HAL_SPI_TransmitReceive_DMA(&spi, dma_tx_buf, dma_rx_buf, 1);
	state = WAIT_RESET;
}

void PressureSensor::callback_reset_tx(void)
{
	main_timer.schedule(&timer, RESET_DELAY, false);
	trace_printf("reset sent\n");
}

void PressureSensor::callback_reset_wait(void)
{
	cs(false);
	state = NOPROM;
	read_prom();
}

void PressureSensor::read_prom(void)
{
	trace_printf("Reading PROM.\n");
	assert(state == NOPROM);
	memset(dma_tx_buf, 0, sizeof(dma_tx_buf));
	dma_tx_buf[0] = CMD_READ_PROM;
	prom_idx = 0;

	cs(true);
	state = WAIT_PROM;
	HAL_SPI_TransmitReceive_DMA(&spi, dma_tx_buf, dma_rx_buf, 3);
}

void PressureSensor::callback_read_prom(void)
{
	cs(false);

	memcpy(&prom[prom_idx*2], &dma_rx_buf[1], 2);
	trace_printf("prom[%u] = %04x\n", prom_idx, dma_rx_buf[1] << 8 | dma_rx_buf[2]);

	prom_idx++;

	if(prom_idx < PROM_SIZE) {
		dma_tx_buf[0] = CMD_READ_PROM + prom_idx*2;
		cs(true);
		HAL_SPI_TransmitReceive_DMA(&spi, dma_tx_buf, dma_rx_buf, 3);
	} else {
		assert(crc4(prom, sizeof(prom)) == 0);
		state = READY;
	}
}

void PressureSensor::enable(void)
{
	dma_rx.Instance = DMA1_Stream3;
	dma_rx.Init.Channel = DMA_CHANNEL_0;
	dma_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	dma_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	dma_rx.Init.MemInc = DMA_MINC_ENABLE;
	dma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dma_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dma_rx.Init.Mode = DMA_NORMAL;
	dma_rx.Init.Priority = DMA_PRIORITY_MEDIUM;
	dma_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	dma_rx.Init.MemBurst = DMA_MBURST_SINGLE;
	dma_rx.Init.PeriphBurst = DMA_PBURST_SINGLE;
	HAL_DMA_Init(&dma_rx);
	__HAL_LINKDMA(&spi, hdmarx, dma_rx);

	dma_tx.Instance = DMA1_Stream4;
	dma_tx.Init.Channel = DMA_CHANNEL_0;
	dma_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	dma_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	dma_tx.Init.MemInc = DMA_MINC_ENABLE;
	dma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dma_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dma_tx.Init.Mode = DMA_NORMAL;
	dma_tx.Init.Priority = DMA_PRIORITY_MEDIUM;
	dma_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
	dma_tx.Init.MemBurst = DMA_MBURST_SINGLE;
	dma_tx.Init.PeriphBurst = DMA_PBURST_SINGLE;
	HAL_DMA_Init(&dma_tx);
	__HAL_LINKDMA(&spi, hdmatx, dma_tx);

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

	HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

	DEPTH_SPI_ENABLE();
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
	HAL_SPI_Init(&spi);
	pin_enable();

	reset();
}

extern "C"
void DMA1_Stream3_IRQHandler(void)
{
	HAL_DMA_IRQHandler(depth.spi.hdmarx);
}

extern "C"
void DMA1_Stream4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(depth.spi.hdmatx);
}

void PressureSensor::callback_dma_complete(void)
{
	switch(state) {
	case WAIT_RESET:
		callback_reset_tx();
		break;
	case WAIT_PROM:
		callback_read_prom();
		break;
	case WAIT_SAMPLE_SEND:
		callback_sample_sent();
		break;
	case WAIT_SAMPLE_RECV:
		callback_sample_done();
		break;
	default:
		assert(0);
	}
}

void PressureSensor::callback_dma_error(void)
{
	trace_printf("DMA error !\n");
	assert(0);
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *spi)
{
	if(spi->Instance != SPI2)
		assert(0);

	depth.callback_dma_complete();
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *spi)
{
	if(spi->Instance != SPI2)
		assert(0);

	depth.callback_dma_complete();
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *spi)
{
	if(spi->Instance != SPI2)
		assert(0);

	depth.callback_dma_complete();
}

void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *spi)
{
	if(spi->Instance != SPI2)
		assert(0);

	depth.callback_dma_error();
}

void PressureSensor::disable(void)
{
	pin_disable();
	HAL_SPI_DeInit(&spi);
	DEPTH_SPI_DISABLE();

	NVIC_DisableIRQ(DMA1_Stream3_IRQn);
	NVIC_DisableIRQ(DMA1_Stream4_IRQn);
	HAL_DMA_DeInit(&dma_rx);
	HAL_DMA_DeInit(&dma_tx);
	state = UNINIT;
}

void PressureSensor::pin_enable(void)
{
	GPIO_InitTypeDef gpio;

	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_LOW;
	gpio.Alternate = DEPTH_MOSI_PIN.af;

	// MOSI
	gpio.Pin = DEPTH_MOSI_PIN.number;
	HAL_GPIO_Init(DEPTH_MOSI_PIN.port, &gpio);

	// SCK
	gpio.Pin = DEPTH_SCK_PIN.number;
	HAL_GPIO_Init(DEPTH_SCK_PIN.port, &gpio);

	// MISO
	gpio.Pin = DEPTH_MISO_PIN.number;
	gpio.Mode = GPIO_MODE_AF_PP;
	HAL_GPIO_Init(DEPTH_MISO_PIN.port, &gpio);

	// CS
	gpio.Pin = DEPTH_CS_PIN.number;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Alternate = 0;
	HAL_GPIO_Init(DEPTH_CS_PIN.port, &gpio);
}

void PressureSensor::pin_disable(void)
{
	HAL_GPIO_DeInit(DEPTH_MOSI_PIN.port, DEPTH_MOSI_PIN.number);
	HAL_GPIO_DeInit(DEPTH_SCK_PIN.port, DEPTH_SCK_PIN.number);
	HAL_GPIO_DeInit(DEPTH_MISO_PIN.port, DEPTH_MISO_PIN.number);
	HAL_GPIO_DeInit(DEPTH_CS_PIN.port, DEPTH_CS_PIN.number);
}

void PressureSensor::sample(DepthSampling osr)
{
	raw_pressure = 0;
	raw_temperature = 0;
	last_pressure = NAN;
	last_temperature = NAN;

	sample_start(CMD_SAMPLE_PRESSURE, osr);
}

void PressureSensor::sample_start(u32 cmd, DepthSampling osr)
{
	assert(osr >= DepthSampling::OSR_256 && osr <= DepthSampling::OSR_4096);
	assert(state == READY || state == WAIT_SAMPLE_RECV);
	const sampling_type_t &sampling = SAMPLING_TYPE[osr];

	sample_cmd = cmd;
	sample_osr = osr;
	dma_tx_buf[0] = sample_cmd | sampling.cmd;
	cs(true);
	HAL_SPI_TransmitReceive_DMA(&spi, dma_tx_buf, dma_rx_buf, 1);
	state = WAIT_SAMPLE_SEND;
}

void PressureSensor::callback_sample_sent(void)
{
	const sampling_type_t &sampling = SAMPLING_TYPE[sample_osr];

	cs(false);
	state = WAIT_SAMPLE_ADC;
	main_timer.schedule(&timer, sampling.delay_us / 1000 + 1, false);
}

void PressureSensor::callback_sample_sampled(void)
{
	cs(true);

	memset(dma_tx_buf, 0, 4);
	dma_tx_buf[0] = CMD_READ_ADC;

	state = WAIT_SAMPLE_RECV;
	HAL_SPI_TransmitReceive_DMA(&spi, dma_tx_buf, dma_rx_buf, 4);
}

void PressureSensor::callback_sample_done(void)
{
	u32 result = dma_rx_buf[1] << 16 | dma_rx_buf[2] << 8 | dma_rx_buf[3];
	cs(false);

	if(sample_cmd == CMD_SAMPLE_PRESSURE) {
		assert(raw_pressure == 0);
		raw_pressure = result;

		sample_start(CMD_SAMPLE_TEMPERATURE, sample_osr);
	} else if(sample_cmd == CMD_SAMPLE_TEMPERATURE) {
		i32 comp_temperature;
		i32 comp_pressure;

		assert(raw_temperature == 0);
		raw_temperature = result;

		convert_values(raw_pressure, raw_temperature, comp_pressure, comp_temperature);
		last_temperature = (float)comp_temperature / 100.0f;
		last_pressure = (float)comp_pressure / 100000.0f;
		FULL_BARRIER();
		state = READY;
	} else
		assert(0);
}

/*
 * Compute CRC-4 over the whole PROM block, returns 0 on success.
 */
u8 PressureSensor::crc4(const u8 *data, size_t size)
{
	u16 rem = 0;

	for(uint i=0; i < size; i++) {
		rem ^= i != size - 1 ? data[i] : data[i] << 4;

		for(int b=8; b > 0; b--)
			rem = rem & 0x8000 ? (rem << 1) ^ 0x3000 : rem << 1;
	}

	return rem >> 12;
}

void PressureSensor::convert_values(u32 pressure_in, u32 temperature_in, i32 &pressure_out, i32 &temperature_out)
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
}

float PressureSensor::get_pressure_bar()
{
	assert(state == READY && !isnan(last_pressure));
	return last_pressure;
}

float PressureSensor::get_temperature_celcius()
{
	assert(state == READY && !isnan(last_pressure));
	return last_temperature;
}

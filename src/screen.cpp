#include <diag/Trace.h>

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_sram.h>
#include <stm32f4xx_hal_gpio.h>

#include "image.h"
#include "screen.h"
#include "types.h"

Screen screen;

static const u32 PORTD_PINS = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
static const u32 PORTE_PINS = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;

u16 * const SCREEN_COMMAND = (u16*)0x60000000;
u16 * const SCREEN_DATA    = (u16*)0x60020000;

// Borrowed from u8glib.
static const u8 init_seq[] = {
		0x0ae,                           /* display off, sleep mode */
		0x0b3, 0x00,                    /* set display clock divide ratio/oscillator frequency */
		0x0a8, 0x03f,                    /* multiplex ratio: 0x03f * 1/64 duty */
		0x0a2, 0x000,                    /* display offset, shift mapping ram counter */
		0x0a1, 0x000,                    /* display start line */
		0x0ad, 0x002,                    /* master configuration: disable embedded DC-DC, enable internal VCOMH */
		0x0a0, 0x052,                    /* remap configuration */
		0x086,                           /* full current range (0x084, 0x085, 0x086) */
		0x0b8,                           /* set gray scale table */
		0x01, 0x011, 0x022, 0x032, 0x043, 0x054, 0x065, 0x076,
		0x081, 0x040,                    /* contrast, brightness, 0..128, Newhaven: 0x040 */
		0x0b2, 0x051,                    /* frame frequency (row period) */
		0x0b1, 0x055,                    /* phase length */
		0x0bc, 0x008,                    /* pre-charge voltage level */
		0x0b4, 0x003,                    /* set pre-charge compensation level (not documented in the SDD1325 datasheet, but used in the NHD init seq.) */
		0x0b0, 0x028,                    /* enable pre-charge compensation (not documented in the SDD1325 datasheet, but used in the NHD init seq.) */
		0x0be, 0x01c,                    /* VCOMH voltage */
		0x0bf, 0x002|0x00d,              /* VSL voltage level (not documented in the SDD1325 datasheet, but used in the NHD init seq.) */
		0x0a5,                           /* all pixel on */
		0x0af,                           /* display on */
};

inline void Screen::cmd(u8 cmd)
{
	*SCREEN_COMMAND = cmd << 8;
	MEMORY_BARRIER;
}

inline void Screen::data(u8 data)
{
	*SCREEN_DATA = data << 8;
	MEMORY_BARRIER;
}

void Screen::enable(void)
{
	SRAM_HandleTypeDef sram;
	FSMC_NORSRAM_TimingTypeDef timing;

	__FSMC_CLK_ENABLE();

	sram.Instance = FSMC_Bank1;
	sram.Extended = FSMC_Bank1E;
	sram.Init.NSBank = FSMC_NORSRAM_BANK1;
	sram.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
	sram.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
	sram.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
	sram.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
	sram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_HIGH;
	sram.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
	sram.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
	sram.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
	sram.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
	sram.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
	sram.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
	sram.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;

	timing.AccessMode = FSMC_ACCESS_MODE_A;
	timing.AddressSetupTime = 15;
	timing.DataSetupTime = 20;
	timing.AddressHoldTime = 1;
	timing.BusTurnAroundDuration = 15;
	timing.CLKDivision = 2;
	timing.DataLatency = 2;

	HAL_SRAM_Init(&sram, &timing, &timing);
	HAL_SRAM_WriteOperation_Enable(&sram);

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_HIGH;
	gpio.Alternate = GPIO_AF12_FSMC;

	gpio.Pin = PORTD_PINS;
	HAL_GPIO_Init(GPIOD, &gpio);

	gpio.Pin = PORTE_PINS;
	HAL_GPIO_Init(GPIOE, &gpio);

	for(unsigned int i=0; i < sizeof(init_seq); i++)
		cmd(init_seq[i]);

	cmd(0xa4);
	cmd(0x15);
	cmd(0);
	cmd(0x3f);
	cmd(0x75);
	cmd(0);
	cmd(0x3f);

	for(uint i=0; i < sizeof(TEST_IMAGE); i++)
		data(TEST_IMAGE[i]);
}

void Screen::disable(void)
{
}

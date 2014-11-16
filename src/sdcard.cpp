#include <diag/Trace.h>
#include <string.h>

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_sd.h>

#include "types.h"
#include "sdcard.h"

SdCard sdcard;

void SdCard::enable(void)
{
	GPIO_InitTypeDef gpio;
	u8 buf[512];

	gpio.Alternate = GPIO_AF12_SDIO;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_HIGH;

	gpio.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	HAL_GPIO_Init(GPIOC, &gpio);

	gpio.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOD, &gpio);

	SD_HandleTypeDef handle;
	HAL_SD_CardInfoTypedef cs;
	HAL_SD_ErrorTypedef err;

	__SDIO_CLK_ENABLE();
	handle.Instance = SDIO;
	handle.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
	handle.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
	handle.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_ENABLE;
	handle.Init.BusWide = SDIO_BUS_WIDE_1B;
	handle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
	handle.Init.ClockDiv = 0;
	err = HAL_SD_Init(&handle, &cs);
	trace_printf("sd init: %u\n", err);

	err = HAL_SD_WideBusOperation_Config(&handle, SDIO_BUS_WIDE_4B);
	trace_printf("sd wide: %u\n", err);

	err = HAL_SD_ReadBlocks(&handle, (u32*)buf, 0, 512, 1);
	trace_printf("sd read: %u\n", err);

}

#include <diag/Trace.h>
#include <string.h>

#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_gpio.h>
#include <stm32f4xx_hal_sd.h>

#include "ff.h"
#include "diskio.h"

#include "types.h"
#include "sdcard.h"

#define BLOCKSIZE 512

SdCard sdcard;
FATFS sdcard_ff;

int SdCard::enable(void)
{
	GPIO_InitTypeDef gpio;

	gpio.Alternate = GPIO_AF12_SDIO;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_PULLUP;
	gpio.Speed = GPIO_SPEED_HIGH;

	gpio.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	HAL_GPIO_Init(GPIOC, &gpio);

	gpio.Pin = GPIO_PIN_2;
	HAL_GPIO_Init(GPIOD, &gpio);

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
	if(err != SD_OK)
		return 1;

	err = HAL_SD_WideBusOperation_Config(&handle, SDIO_BUS_WIDE_4B);
	trace_printf("sd wide: %u\n", err);
	if(err != SD_OK)
		return 1;

	trace_printf("card capacity: %u MiB\n", (u32)(cs.CardCapacity / (1024*1024)));
	return 0;
}

DSTATUS disk_status (BYTE pdrv)
{
	if(pdrv != SDCARD_DRIVE)
		return STA_NOINIT;

	return 0;
}

DSTATUS disk_initialize (BYTE pdrv)
{
	trace_printf("disk_initialize drv: %d\n", pdrv);
	if(pdrv != SDCARD_DRIVE)
		return STA_NOINIT;

	if(sdcard.enable() != 0)
		return STA_NOINIT;
	else
		return 0;
}

DRESULT disk_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count)
{
	HAL_SD_ErrorTypedef sderr;
	u64 addr = (u64)sector * BLOCKSIZE;

	trace_printf("disk_read drv=%d %d@%d\n", pdrv, count, sector);
	if(pdrv != SDCARD_DRIVE)
		return RES_PARERR;


	sderr = HAL_SD_ReadBlocks(&sdcard.handle, (uint32_t*)buff, addr, BLOCKSIZE, count);

	return sderr == SD_OK ? RES_OK : RES_PARERR;
}

#if _USE_WRITE
DRESULT disk_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count)
{
	trace_printf("disk_write drv=%d %d@%d\n", pdrv, count, sector);
	HAL_SD_ErrorTypedef sderr;
	u64 addr = (u64)sector * BLOCKSIZE;

	if(pdrv != SDCARD_DRIVE)
		return RES_PARERR;

	sderr = HAL_SD_WriteBlocks(&sdcard.handle, (uint32_t*)buff, addr, BLOCKSIZE, count);

	return sderr == SD_OK ? RES_OK : RES_PARERR;
}
#endif

#if _USE_IOCTL
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void *buff)
{
	if(pdrv != SDCARD_DRIVE)
		return RES_PARERR;

	switch(cmd) {
	case CTRL_SYNC:
		// no write cache
		return RES_OK;
	}

	return RES_PARERR;
}
#endif

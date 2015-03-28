//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <diag/Trace.h>
#include <cortexm/ExceptionHandlers.h>

#include <array>

#include <stm32f4xx_hal.h>

#include "depth.h"
#include "sdcard.h"
#include "screen.h"
#include "timer.h"
#include "types.h"

static void rtc_init(void) {
	HAL_PWR_EnableBkUpAccess();

	__HAL_RCC_LSE_CONFIG(RCC_LSE_ON); unsigned
	int loop = 0;

	for (; __HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == 0; loop++)
		__WFI();

	trace_printf("LSE ready after %d loops.\n", loop);

	__HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE); __HAL_RCC_RTC_ENABLE();
}

int main(void) {
	char buf1[16], buf2[16];
#ifdef DEBUG
	HAL_EnableDBGSleepMode();
#endif

	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();
	__GPIOD_CLK_ENABLE();
	__GPIOE_CLK_ENABLE();

	__DMA1_CLK_ENABLE();
	__DMA1_CLK_SLEEP_ENABLE();

	SysTick_Config(SystemCoreClock / 8 / 1000);
	__HAL_CORTEX_SYSTICKCLK_CONFIG(SYSTICK_CLKSOURCE_HCLK_DIV8);
	NVIC_SetPriority(SysTick_IRQn, 0);

	DepthSampling sampling = DepthSampling::OSR_4096;

	trace_printf("System clock: %uHz\n", SystemCoreClock);
	rtc_init();
	trace_printf("RTC ready to go.\n");
	screen.enable();
	depth.enable();
	assert(depth.wait());
	trace_printf("Depth sensor ready to go.\n");
	u32 temperature, pressure;
	i32 comp_pressure;
	i32 comp_temperature;
	FRESULT fres;

	fres = f_mount(&sdcard_ff, "0", 1);
	trace_printf("fres mount: %d\n", fres);
	{
		DIR d;
		FILINFO fi;

		char lfn[_MAX_LFN + 1];
		fi.lfname = lfn;
		fi.lfsize = sizeof(lfn);

		fres = f_opendir(&d, "/");
		trace_printf("fres opendir: %d\n", fres);

		for(;;) {
			fres = f_readdir(&d, &fi);
			if(fres != FR_OK || fi.fname[0] == 0)
				break;

			trace_printf("file: %s\n", *fi.lfname ? fi.lfname : fi.fname);
		}
		f_closedir(&d);
	}
	FIL f;
	fres = f_open(&f, "/log.txt", FA_WRITE | FA_OPEN_ALWAYS);
	trace_printf("fres open: %d\n", fres);
	fres = f_lseek(&f, f_size(&f));
	trace_printf("fres seek: %d\n", fres);

	for (;;) {
		depth.sample(sampling, &pressure, &temperature);
		HAL_Delay(100);
		depth.wait();

		depth.convert_values(pressure, temperature, comp_pressure,
				comp_temperature);

		snprintf(buf1, sizeof(buf1), "%04ld.%02ld mbar\n", comp_pressure / 100,
				comp_pressure % 100);
		fres = f_write(&f, buf1, strlen(buf1), NULL);
		snprintf(buf2, sizeof(buf2), "%ld.%02ld C\n", comp_temperature / 100,
				(comp_temperature > 0 ? comp_temperature : -comp_temperature)
						% 100);
		fres = f_write(&f, buf2, strlen(buf2), NULL);

		fres = f_sync(&f);
		trace_printf("fres sync: %d\n", fres);
		u8g_FirstPage(&screen.u8g);
		do {
			u8g_SetColorIndex(&screen.u8g, 1);

			u8g_DrawHLine(&screen.u8g, 0, 0, 128);
			u8g_DrawHLine(&screen.u8g, 0, 63, 128);
			u8g_DrawVLine(&screen.u8g, 0, 0, 64);
			u8g_DrawVLine(&screen.u8g, 127, 0, 64);

			u8g_SetColorIndex(&screen.u8g, 3);
			u8g_SetFont(&screen.u8g, u8g_font_ncenR12);
			u8g_DrawStr(&screen.u8g, 10, 27, buf1);

			u8g_SetColorIndex(&screen.u8g, 2);
			u8g_SetFont(&screen.u8g, u8g_font_ncenR12);
			u8g_DrawStr(&screen.u8g, 28, 46, buf2);
		} while (u8g_NextPage(&screen.u8g));
	}

}

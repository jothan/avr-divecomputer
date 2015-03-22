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

const float pascal_to_meter = 0.0001019977334;
const float bar_to_meter = 0.09804139432;

//pressure water vapour
const float pressure_water = 0.0627;
const float initialAmbienPressure = 1.013;

const float buehlmann_N2_a[] = { 1.1696, 1.0, 0.8618, 0.7562, 0.62, 0.5043,
		0.441, 0.4, 0.375, 0.35, 0.3295, 0.3065, 0.2835, 0.261, 0.248, 0.2327 };

const float buehlmann_N2_b[] = { 0.5578, 0.6514, 0.7222, 0.7825, 0.8126, 0.8434,
		0.8693, 0.8910, 0.9092, 0.9222, 0.9319, 0.9403, 0.9477, 0.9544, 0.9602,
		0.9653 };

//buehlmann with 1b value
const float buehlmann_N2_t_halflife[] = { 5.0, 8.0, 12.5, 18.5, 27.0, 38.3,
		54.3, 77.0, 109.0, 146.0, 187.0, 239.0, 305.0, 390.0, 498.0, 635.0 };

const float buehlmann_He_a[] = { 1.6189, 1.383, 1.1919, 1.0458, 0.922, 0.8205,
		0.7305, 0.6502, 0.595, 0.5545, 0.5333, 0.5189, 0.5181, 0.5176, 0.5172,
		0.5119 };

const float buehlmann_He_b[] = { 0.4770, 0.5747, 0.6527, 0.7223, 0.7582, 0.7957,
		0.8279, 0.8553, 0.8757, 0.8903, 0.8997, 0.9073, 0.9122, 0.9171, 0.9217,
		0.9267 };

const double buehlmann_He_t_halflife[] =
		{ 1.88, 3.02, 4.72, 6.99, 10.21, 14.48, 20.53, 29.11, 41.20, 55.19,
				70.69, 90.34, 115.29, 147.42, 188.24, 240.03 };

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
	sdcard.enable();
	depth.enable();

	assert(depth.wait());
	trace_printf("Depth sensor ready to go.\n");
	u32 temperature, pressure;

	//number of tissue
	const int MAX_TISSUE = 16;

	//one array by gaz
	float tabN2[MAX_TISSUE] = { };
	float tabH2[MAX_TISSUE] = { };

	//should be variable from a menu to manage: air, nitrox, trimix
	float NITROGEN_AIR = 0.79;

	i32 comp_pressure;
	i32 comp_temperature;

	//initialize model, previous table array should be initialized from file system if 24 hours is not gone from last dive
	depth.sample(sampling, &pressure, &temperature);
	depth.wait();
	depth.convert_values(pressure, temperature, comp_pressure,
			comp_temperature);
	float ambiant_pressure = comp_pressure / 100000;
	trace_printf("---%f---", ambiant_pressure);
	for (int i = 0; i < MAX_TISSUE; i++) {
		tabN2[i] = NITROGEN_AIR * (ambiant_pressure - pressure_water);
	}

	trace_printf("---%f---", tabN2[0]);

	for (;;) {

//		i32 comp_pressure;
//		i32 comp_temperature;
		depth.sample(sampling, &pressure, &temperature);
		HAL_Delay(100);
		depth.wait();

		depth.convert_values(pressure, temperature, comp_pressure,
				comp_temperature);

		snprintf(buf1, sizeof(buf1), "%04ld.%02ld mbar ", comp_pressure / 100,
				comp_pressure % 100);
		snprintf(buf2, sizeof(buf2), "%ld.%02ld C", comp_temperature / 100,
				(comp_temperature > 0 ? comp_temperature : -comp_temperature)
						% 100);
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

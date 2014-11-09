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

#include <stm32f4xx_hal.h>

#include "depth.h"
#include "timer.h"
#include "types.h"

static void rtc_init(void)
{
	HAL_PWR_EnableBkUpAccess();

	__HAL_RCC_LSE_CONFIG(RCC_LSE_ON);
	unsigned int loop=0;

	for(;__HAL_RCC_GET_FLAG(RCC_FLAG_LSERDY) == 0; loop++)
		__WFI();

	trace_printf("LSE ready after %d loops.\n", loop);


	__HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
	__HAL_RCC_RTC_ENABLE();
}

int main(void)
{
#ifdef DEBUG
	HAL_EnableDBGSleepMode();
#endif

	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	__DMA1_CLK_ENABLE();
	__DMA1_CLK_SLEEP_ENABLE();

	SysTick_Config(SystemCoreClock / 8 / 1000);
	__HAL_CORTEX_SYSTICKCLK_CONFIG(SYSTICK_CLKSOURCE_HCLK_DIV8);
	NVIC_SetPriority(SysTick_IRQn, 0);

	DepthSampling sampling =  DepthSampling::OSR_4096;

	trace_printf("System clock: %uHz\n", SystemCoreClock);
	rtc_init();
	trace_printf("RTC ready to go.\n");
	depth.enable();

	assert(depth.wait());
	trace_printf("Depth sensor ready to go.\n");
	u32 temperature, pressure;
	for(;;) {
		depth.sample(sampling, &pressure, &temperature);
		HAL_Delay(1000);
		depth.wait();

		i32 comp_pressure;
		i32 comp_temperature;
		depth.convert_values(pressure, temperature, comp_pressure, comp_temperature);
		trace_printf("%4d.%02d mbar, %d.%02d C\n", comp_pressure / 100, comp_pressure % 100, comp_temperature / 100, (comp_temperature > 0 ? comp_temperature : -comp_temperature) % 100);
	}

}

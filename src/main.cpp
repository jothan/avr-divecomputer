//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stm32f4xx_hal.h>
#include "stm32f4xx_hal_gpio.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <array>

#include "pressureSensor.h"
#include "rtc.h"
#include "sdcard.h"
#include "screen.h"
#include <time.h> 
#include "timer.h"
#include "types.h"
#include "pins.h"
#include "buhlmannModel.h"
#include "systemClock.h"
#include "waterSensor.h"
#include "fileUtility.h"
#include <diag/Trace.h>

static inline void enable_peripherals() {
    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
    __GPIOE_CLK_ENABLE();
    __DMA1_CLK_ENABLE();
    __DMA1_CLK_SLEEP_ENABLE();
}

int main(void) {
    char buf1[16], buf2[32];
#ifdef DEBUG
    HAL_EnableDBGSleepMode();
#endif
    enable_peripherals();
    rtc.init();

    SysTick_Config(SystemCoreClock / 8 / 1000);
    __HAL_CORTEX_SYSTICKCLK_CONFIG(SYSTICK_CLKSOURCE_HCLK_DIV8);
    NVIC_SetPriority(SysTick_IRQn, 0);

    DepthSampling sampling = DepthSampling::OSR_4096;

    trace_printf("System clock: %uHz\n", SystemCoreClock);
    screen.enable();
    pressureSensor.enable();

    //    assert(pressureSensor.wait());
    //    pressureSensor.sample(sampling);
    trace_printf("Depth sensor ready to go.\n");

    float temperature, pressure;
    systemClock.setDate(1, 5, 15);
    systemClock.setTime(18, 16, 0);
    
//    systemClock.getTime();
//    systemClock.getDate();
    time_t start = systemClock.getUnixTimestamp();
    //trace_printf("time %lu\n", (long) systemClock.getUnixTimestamp());
    
    HAL_Delay(5000);
//    systemClock.getTime();
//    systemClock.getDate();
    //trace_printf("time %lu\n", (long) systemClock.getUnixTimestamp());

    time_t end = systemClock.getUnixTimestamp();
    
    trace_printf("Tu t'es absente pendant %f secondes.", difftime(end, start));
    
    
    FileUtility fileUtility("");
    
    for (;;) {

        //if clicked a button, start to calculate pressure

        pressureSensor.capture_data();
        float current_pressure = pressureSensor.get_pressure_bar();

        snprintf(buf1, sizeof (buf1), "%.2f mbar\n", pressure * 1000.);

       snprintf(buf1, sizeof (buf1), "%.2f mbar", pressure * 1000.);
        time_t tm = rtc.now();
        ctime_r(&tm, buf2);

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
            u8g_SetFont(&screen.u8g, u8g_font_helvR08);
            u8g_DrawStr(&screen.u8g, 4, 46, buf2);
        } while (u8g_NextPage(&screen.u8g));


        //dive start when diver have started to descend to min 100 centimeter
        if (waterSensor.is_wet() && current_pressure - pressureSensor.get_atm_pressure() > 0.1) {
            trace_printf("diving start\n");
            pressureSensor.capture_data();
            pressure = pressureSensor.get_pressure_bar();
            temperature = pressureSensor.get_temperature_celcius();

            HAL_Delay(1000);
        } else { // should check if the pressure is around the atm

            pressureSensor.capture_data();
            pressure = pressureSensor.get_pressure_bar();

            trace_printf("diving end\n");
            HAL_Delay(10000);
        }

        //if desaturation is finish we can return in sleep mode
        __WFI();
    }
}

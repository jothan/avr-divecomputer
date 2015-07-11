#include <assert.h>
#include <time.h> 
#include <diag/Trace.h>

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_rtc_ex.h"

#include "rtc.h"
#include "types.h"

Rtc rtc;

Rtc::Rtc(void)
{
    handle.Init.HourFormat = RTC_HOURFORMAT_24;
    handle.Init.AsynchPrediv = 127;
    handle.Init.SynchPrediv = (LSE_VALUE / 128) - 1;
    handle.Init.OutPut = RTC_OUTPUT_DISABLE;
    handle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    handle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

    handle.Instance = RTC;
}

bool Rtc::init(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RTC_DateTypeDef dateStruct;
    RTC_TimeTypeDef timeStruct;

    // Enable access to Backup domain
    HAL_PWR_EnableBkUpAccess();

    if(HAL_RTCEx_BKUPRead(&handle, RTC_BKP_DR0) == RTC_MAGIC) {
	trace_printf("RTC already initialized, leaving it alone.\n");
	return false;
    }
    trace_printf("Resetting RTC.\n");

    // Reset Backup domain
    __HAL_RCC_BACKUPRESET_FORCE();
    __HAL_RCC_BACKUPRESET_RELEASE();

    // Enable LSE Oscillator
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE; /* Mandatory, otherwise the PLL is reconfigured! */
    RCC_OscInitStruct.LSEState = RCC_LSE_ON; /* External 32.768 kHz clock on OSC_IN/OSC_OUT */
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) == HAL_OK) {
        // Connect LSE to RTC
        __HAL_RCC_RTC_CLKPRESCALER(RCC_RTCCLKSOURCE_LSE);
        __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
    }

    // Enable RTC
    __HAL_RCC_RTC_ENABLE();
    trace_printf("DR0 = %x %x\n", HAL_RTCEx_BKUPRead(&handle, RTC_BKP_DR0), RTC_MAGIC);

    if (HAL_RTC_Init(&handle) != HAL_OK) {
        trace_printf("RTC error: RTC initialization failed.\n");
	assert(0);
    }

    dateStruct.WeekDay = RTC_WEEKDAY_MONDAY;
    dateStruct.Month = RTC_MONTH_JANUARY;
    dateStruct.Date = 1;
    dateStruct.Year = 15;


    timeStruct.Hours = 0;
    timeStruct.Minutes = 0;
    timeStruct.Seconds = 0;
    timeStruct.TimeFormat = RTC_HOURFORMAT12_PM;
    timeStruct.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    timeStruct.StoreOperation = RTC_STOREOPERATION_RESET;

    HAL_RTC_SetDate(&handle, &dateStruct, FORMAT_BIN);
    HAL_RTC_SetTime(&handle, &timeStruct, FORMAT_BIN);

    HAL_RTCEx_BKUPWrite(&handle, RTC_BKP_DR0, RTC_MAGIC);

    return true;
}

time_t Rtc::now(void)
{
    RTC_DateTypeDef dateStruct;
    RTC_TimeTypeDef timeStruct;
    struct tm timeinfo;

    HAL_RTC_GetTime(&handle, &timeStruct, FORMAT_BIN);
    HAL_RTC_GetDate(&handle, &dateStruct, FORMAT_BIN);

    // Setup a tm structure based on the RTC
    timeinfo.tm_wday = dateStruct.WeekDay;
    timeinfo.tm_mon = dateStruct.Month - 1;
    timeinfo.tm_mday = dateStruct.Date;
    timeinfo.tm_year = dateStruct.Year + 100;
    timeinfo.tm_hour = timeStruct.Hours;
    timeinfo.tm_min = timeStruct.Minutes;
    timeinfo.tm_sec = timeStruct.Seconds;

    return mktime(&timeinfo);
}

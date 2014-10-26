//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "BlinkLed.h"

namespace
{
  // ----- Timing definitions -------------------------------------------------

  // Keep the LED on for 2/3 of a second.
  constexpr Timer::ticks_t BLINK_ON_TICKS = Timer::FREQUENCY_HZ *2/3;
  constexpr Timer::ticks_t BLINK_OFF_TICKS = Timer::FREQUENCY_HZ - BLINK_ON_TICKS;
}

static void rtc_init(void)
{
	HAL_PWR_EnableBkUpAccess();
	trace_printf("RCC_CSR = %08x\n", RCC->CSR);

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
  trace_printf("System clock: %uHz\n", SystemCoreClock);
  rtc_init();
  trace_printf("RTC ready to go.\n");

  Timer timer;
  timer.start();

  BlinkLed blinkLed;

  blinkLed.powerUp();

  for(;;) {
      blinkLed.turnOn();
      timer.sleep(BLINK_ON_TICKS);

      blinkLed.turnOff();
      timer.sleep(BLINK_OFF_TICKS);

    }
}

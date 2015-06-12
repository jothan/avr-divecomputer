/*
 * systemClock.h
 *
 *  Created on: 28 april. 2015
 *      Author: collinm
 */

#include "stm32f4xx_hal_rtc.h"
#include "types.h"
#include <time.h> 

#ifndef SYSTEMCLOCK_H_
#define SYSTEMCLOCK_H_

class SystemClock {
public:
    SystemClock();
    ~SystemClock();
    time_t getUnixTimestamp();
    RTC_DateTypeDef getDate();
    RTC_TimeTypeDef getTime();
    void setDate(uint8_t day, uint8_t month, uint8_t years);
    void setTime(uint8_t hours, uint8_t minute, uint8_t seconds);
private:
    RTC_HandleTypeDef RtcHandle;
    RTC_DateTypeDef dateStruct;
    RTC_TimeTypeDef timeStruct;
};

extern SystemClock systemClock;

#endif /* SYSTEMCLOCK_H_ */

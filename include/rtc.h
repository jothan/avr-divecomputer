#ifndef RTC_H
#define RTC_H

#include "types.h"

class Rtc
{
public:
    Rtc(void);
    bool init(void);
    time_t now(void);
protected:
    const u32 RTC_MAGIC = 0x1badcafe;
    RTC_HandleTypeDef handle;
};

extern Rtc rtc;

#endif

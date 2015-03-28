#ifndef SDCARD_H
#define SDCARD_H

#include "ff.h"
#include "integer.h"

#ifdef __cplusplus
class SdCard
{
public:
	int enable(void);
	void disable(void);
	SD_HandleTypeDef handle;
};

extern SdCard sdcard;
#endif

#define SDCARD_DRIVE 0
extern FATFS sdcard_ff;

#endif

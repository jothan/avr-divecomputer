#ifndef SDCARD_H
#define SDCARD_H

#include <avr/pgmspace.h>

#include "diskio.h"
#include "spi.h"

DSTATUS sdcard_initialize(void);
DSTATUS sdcard_disk_status(void);
DRESULT sdcard_disk_ioctl(BYTE cmd, void *buff);

DRESULT sdcard_disk_read(const BYTE *byte, DWORD sector, UINT count);
DRESULT sdcard_disk_write(const BYTE *byte, DWORD sector, UINT count);

extern const spi_device_t sdcard_device;

#endif

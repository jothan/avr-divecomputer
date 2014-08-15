#include "diskio.h"

DSTATUS sdcard_initialize(void);
DSTATUS sdcard_disk_status(void);
DRESULT sdcard_disk_ioctl(BYTE cmd, void *buff);

DRESULT sdcard_disk_read(const BYTE *byte, DWORD sector, UINT count);
DRESULT sdcard_disk_write(const BYTE *byte, DWORD sector, UINT count);


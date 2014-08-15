#include "sdcard.h"

DSTATUS sdcard_initialize(void)
{
	return 0;
}

DSTATUS sdcard_disk_status(void)
{
	return 0;
}

DRESULT sdcard_disk_ioctl(BYTE cmd, void *buff)
{
	return 0;
}

DRESULT sdcard_disk_read(const BYTE *byte, DWORD sector, UINT count)
{
	return 0;
}

DRESULT sdcard_disk_write(const BYTE *byte, DWORD sector, UINT count)
{
	return 0;
}

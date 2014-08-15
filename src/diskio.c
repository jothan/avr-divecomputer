/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "sdcard.h"

/* Definitions of physical drive number for each media */
#define SDC		0


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (BYTE pdrv)
{
	switch (pdrv) {
	case SDC :
		return sdcard_initialize();
	}
	return STA_NOINIT;
}



DSTATUS disk_status (BYTE pdrv)
{
	switch (pdrv) {
	case SDC:
		return sdcard_disk_status();
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	UINT count		/* Number of sectors to read (1..128) */
)
{
	switch (pdrv) {
	case SDC:
		return sdcard_disk_read(buff, sector, count);
	}
	return RES_PARERR;
}

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	UINT count		/* Number of sectors to write (1..128) */
)
{
	switch (pdrv) {
	case SDC:
		return sdcard_disk_write(buff, sector, count);
	}
	return RES_PARERR;
}

DWORD get_fattime(void)
{
	return 0;
}
#endif

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	switch (pdrv) {
	case SDC:
		return sdcard_disk_ioctl(cmd, buff);
	}
	return RES_PARERR;
}
#endif

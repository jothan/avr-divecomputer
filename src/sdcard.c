#include <avr/sfr_defs.h>

#include "spi.h"
#include "sdcard.h"
#include "types.h"
#include "pins.h"

#define SPEED_INITIAL 400000
#define SPEED_MAX F_CPU

static i8 _spi_init(void)
{
	PIN_SET(SDCARD_CS);
	PIN_OUTPUT(SDCARD_CS);
	return 0;
}

static i8 _spi_setup(void)
{
	spi_set_speed(SPEED_INITIAL);
	return 0;
}

static i8 _spi_acquire(void)
{
	PIN_CLEAR(SDCARD_CS);
	return 0;
}

static i8 _spi_release(void)
{
	PIN_SET(SDCARD_CS);
	spi_shift(0xff);
	return 0;
}

const spi_device_t sdcard_device = {
	.init = &_spi_init,
	.setup = &_spi_setup,
	.acquire = &_spi_acquire,
	.release = &_spi_release,
};


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

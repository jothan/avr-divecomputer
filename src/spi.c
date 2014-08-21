#include <stddef.h>

#include <avr/power.h>

#include "spi.h"
#include "sdcard.h"

const spi_device_t* const spi_devices[] = {&sdcard_device};

const spi_device_t *active_device;

void spi_init(void)
{
	for(u8 i=0; i < sizeof(spi_devices); i++) {
		const spi_device_t *dev = spi_devices[i];
		dev->init();
	}
}

void spi_enable(void)
{
	power_spi_enable();
	SPCR = _BV(SPE) | _BV(MSTR);
}

void spi_disable(void)
{
	if(active_device) {
		active_device->release();
		active_device = NULL;
	}
	power_spi_disable();
}

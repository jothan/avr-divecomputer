#include <stddef.h>

#include <avr/power.h>

#include "pins.h"
#include "spi.h"
#include "sdcard.h"

const spi_device_t *active_device;

void spi_init(u8 nb)
{
	for(u8 i=0; i < nb; i++) {
		const spi_device_t *dev = spi_devices[i];
		dev->init();
	}
}

void spi_enable(void)
{
	power_spi_enable();

	PIN_CLEAR(SPI_CLK);
	PIN_OUTPUT(SPI_CLK);
	PIN_OUTPUT(SPI_MOSI);

	PIN_INPUT(SPI_MISO);
	PIN_SET(SPI_MISO);
	
	SPCR = _BV(SPE) | _BV(MSTR);
	spi_set_div(128);
}

void spi_disable(void)
{
	spi_unselect();

	PIN_INPUT(SPI_CLK);
	PIN_SET(SPI_CLK);
	PIN_INPUT(SPI_MOSI);
	PIN_SET(SPI_MOSI);
	PIN_INPUT(SPI_MISO);
	PIN_SET(SPI_MISO);

	SPCR = 0;
	power_spi_disable();
}

void spi_select(const spi_device_t *device)
{
	if(active_device != device) {
		active_device->release();
		active_device = device;
		device->setup();
	}
	active_device = device;
	device->acquire();
}

void spi_unselect(void)
{
	if(active_device) {
		active_device->release();
		active_device = NULL;
	}
}

void spi_set_speed(u32 hz)
{
	// hz is maximum speed
	spi_set_div(F_CPU / hz);
}

void spi_set_div(u8 div)
{
	u8 x2, r;

	switch(div) {
	case 2:
		x2 = 1;
		r = 0;
		break;
	case 4:
		x2 = 0;
		r = 0;
		break;
	case 8:
		x2 = 1;
		r = _BV(SPR0);
		break;
	case 16:
		x2 = 0;
		r = _BV(SPR0);
		break;
	case 32:
		x2 = 1;
		r = _BV(SPR1);
		break;
	case 64:
		x2 = 1;
		r = _BV(SPR1) | _BV(SPR0);
		break;
	case 128:
		x2 = 0;
		r = _BV(SPR1) | _BV(SPR0);
		break;
	default:
		// Round up to slowest clock
		if(div <= 1)
			spi_set_div(2);
		else
			spi_set_div(1 << log2(div));
		return;
	}

	SPCR = (SPCR & ~(_BV(SPR1) | _BV(SPR0))) | r;

	if(x2)
		SPSR |= _BV(SPI2X);
	else
		SPSR &= ~(_BV(SPI2X));
}

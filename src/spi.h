#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

#include "types.h"

typedef struct {
	// Called once at boot. Setup CS as an output here.
	i8 (*init)(void);
	// Used for speed initialisation and other bus setup.
	i8 (*setup)(void);
	// Used to drive the CS line low.
	i8 (*acquire)(void);
	// Used to drive the CS line high.
	i8 (*release)(void);
} spi_device_t;

static inline u8 spi_shift(u8 output)
{
	SPDR = output;
	loop_until_bit_is_set(SPSR, SPIF);

	return SPDR;
}

void spi_init(u8 nb);
void spi_enable(void);
void spi_disable(void);
void spi_select(const spi_device_t *device);
void spi_unselect(void);
void spi_set_speed(u32 hz);
void spi_set_div(u8 div);


extern const spi_device_t* const spi_devices[];

#endif

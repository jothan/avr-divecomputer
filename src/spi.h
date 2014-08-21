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

void spi_init(void);
void spi_disable(void);

#endif

#ifndef PINS_H
#define PINS_H

#include <stm32f4xx_hal_rcc.h>

#include "types.h"

typedef struct {
	GPIO_TypeDef *port;
	u32 number;
} pin_t;

// Prototype 1
extern const pin_t DEPTH_MOSI_PIN;
extern const pin_t DEPTH_MISO_PIN;
extern const pin_t DEPTH_SCK_PIN;
extern const pin_t DEPTH_CS_PIN;

#define DEPTH_SPI SPI2
#define DEPTH_SPI_ENABLE __SPI2_CLK_ENABLE
#define DEPTH_SPI_DISABLE __SPI2_CLK_DISABLE
#define DEPTH_SPI_AF GPIO_AF5_SPI2

#endif

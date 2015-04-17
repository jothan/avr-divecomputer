#ifndef PINS_H
#define PINS_H

#include <stm32f4xx_hal_rcc.h>

#include "types.h"

typedef struct {
	GPIO_TypeDef *port;
	u32 number;
	u8 af;
} pin_t;

#define PIN_DEF(NAME, PORT, PIN) static const pin_t NAME = {.port=PORT, .number=PIN, .af=0};
#define PIN_DEF_AF(NAME, PORT, PIN, AF) static const pin_t NAME = {.port=PORT, .number=PIN, .af=AF};

// Prototype 1
PIN_DEF_AF(DEPTH_MOSI_PIN, GPIOB ,GPIO_PIN_15, GPIO_AF5_SPI2);
PIN_DEF_AF(DEPTH_MISO_PIN, GPIOC, GPIO_PIN_2, GPIO_AF5_SPI2);
PIN_DEF_AF(DEPTH_SCK_PIN, GPIOB, GPIO_PIN_13, GPIO_AF5_SPI2);
PIN_DEF(DEPTH_CS_PIN, GPIOB, GPIO_PIN_14);

#define DEPTH_SPI SPI2
#define DEPTH_SPI_ENABLE __SPI2_CLK_ENABLE
#define DEPTH_SPI_DISABLE __SPI2_CLK_DISABLE

#endif

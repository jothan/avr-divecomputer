#include <stm32f4xx_hal.h>

#include "pins.h"

const pin_t DEPTH_MOSI_PIN = {.port = GPIOB, .number = GPIO_PIN_15};
const pin_t DEPTH_MISO_PIN = {.port = GPIOC, .number = GPIO_PIN_2};
const pin_t DEPTH_SCK_PIN = {.port = GPIOB, .number = GPIO_PIN_13};
const pin_t DEPTH_CS_PIN = {.port = GPIOB, .number = GPIO_PIN_14};

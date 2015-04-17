/* 
 * File:   waterSensor.cpp
 * Author: collinm
 * 
 * Created on 15 avril 2015, 21:15
 */

#include "waterSensor.h"

#include <stm32f4xx_hal.h>
#include "stm32f4xx_hal_gpio.h"


WaterSensor::WaterSensor() 
{
}


WaterSensor::~WaterSensor() 
{
}

bool WaterSensor::is_wet()
{
    //1 = wet, 0= dry
    return !HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)!=0;
}


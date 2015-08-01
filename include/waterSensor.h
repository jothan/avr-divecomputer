/* 
 * File:   waterSensor.h
 * Author: collinm
 *
 * Created on 15 avril 2015, 21:14
 */

#ifndef WATERSENSOR_H
#define	WATERSENSOR_H

class WaterSensor {
public:
    WaterSensor();
    ~WaterSensor();
    bool is_wet();
};

extern WaterSensor waterSensor;

#endif
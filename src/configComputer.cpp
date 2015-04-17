#include "configComputer.h"

ConfigComputer configComputer;

float ConfigComputer::get_hydrostatic_pressure(){
    if(defaultWaterType==waterType::FreshWater){
        return 0.98;
    }
    //salt water
    return 1.007;
}


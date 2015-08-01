#include "configComputer.h"
#include "constants.h"
//#include "computerGazEnum.h"

ConfigComputer configComputer;

void ConfigComputer::set_system_unit(unitSystem unitsType){
    this->units = unitsType;
}

unitSystem ConfigComputer::get_system_unit() {
    return units;
}

waterType ConfigComputer::get_wather_type() {
    return defaultWaterType;
}

conservatismeLevel ConfigComputer::get_conservatisme_level(){
    return conservatisme;
}

void ConfigComputer::set_conservatisme_level(conservatismeLevel conservatisme){
    this->conservatisme = conservatisme;
}

float ConfigComputer::get_hydrostatic_pressure() {
    if (defaultWaterType == waterType::FreshWater) {
        return GlobalConstants::fresh_waster_hydrostatic;
    }
    //salt water
    return GlobalConstants::salt_water_hydrostactif;
}

void ConfigComputer::setPo2Allowed(float pO2){
    this->pO2Allowed = pO2;
}

float ConfigComputer::getPo2Allowed(){
    return pO2Allowed;
}


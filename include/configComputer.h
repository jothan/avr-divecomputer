
#include "langEnum.h"
#include "waterTypeEnum.h"
#include "unitEnum.h"
#include "conservatisme.h"

class ConfigComputer {
    lang default_lang = lang::eng;
    waterType defaultWaterType = waterType::FreshWater;
    unitSystem units = unitSystem::Metric;
    conservatismeLevel  conservatisme = conservatismeLevel::Normal;
    float pO2Allowed = 1.4;
    
    //ne pas permettre 100/100
    float gradient_low;
    float gradient_hi;
    
public:
    float get_hydrostatic_pressure();
    void set_system_unit(unitSystem unit);
    unitSystem get_system_unit();

    waterType get_wather_type();
    void set_wather_type(waterType waterType);
    conservatismeLevel get_conservatisme_level();
    void set_conservatisme_level(conservatismeLevel conservatisme);
    void setPo2Allowed(float pO2);
    float getPo2Allowed();
};


extern ConfigComputer configComputer;
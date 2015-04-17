#include "computerGazEnum.h"
#include "langEnum.h"
#include "waterTypeEnum.h"
#include "unitEnum.h"

class ConfigComputer {
	gazType computerGaz=gazType::Air;
	lang default_lang=lang::eng;
        waterType defaultWaterType=waterType::FreshWater;
	unitSystem units = unitSystem::Metric;
        float hydrostaticPressure;
public:
    float get_hydrostatic_pressure();
};


extern ConfigComputer configComputer;
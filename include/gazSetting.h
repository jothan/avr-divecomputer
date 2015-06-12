#ifndef GAZSETTING_H_
#define GAZSETTING_H_

#include "computerGazEnum.h"

class GazSetting {
public:
    GazSetting();
    ~GazSetting();
    gazType computerGaz = gazType::Air;
    float getO2Percentage();
    float getN2Percentage();
    float getHe2Percentage();
    void setO2Percentage(float o2Percentage);
    void setN2Percentage(float n2Percentage);
    void setHe2Percentage(float he2Percentage);
    void setGazSetting(float o2Percentage, float he2Percentage);
private:
    float o2Percentage;
    float n2Percentage;
    float he2Percentage;
};

extern GazSetting gazSetting;

#endif
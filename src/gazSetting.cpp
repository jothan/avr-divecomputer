#include "gazSetting.h"

float GazSetting::getO2Percentage() {
    return o2Percentage;
}

float GazSetting::getN2Percentage() {
    return n2Percentage;
}

float GazSetting::getHe2Percentage() {
    return he2Percentage;
}

void GazSetting::setO2Percentage(float o2Percentage) {
    this->o2Percentage=o2Percentage;
}

void GazSetting::setN2Percentage(float n2Percentage) {
    this->n2Percentage=n2Percentage;
}

void GazSetting::setHe2Percentage(float he2Percentage) {
    this->he2Percentage=he2Percentage;
}

void GazSetting::setGazSetting(float o2Percentage, float he2Percentage) {
    this->o2Percentage = o2Percentage;
    this->he2Percentage = he2Percentage;
    this->n2Percentage = 100 - o2Percentage - he2Percentage;
}
/*
 * BuhlmannModel.cpp
 *
 *  Created on: 24 févr. 2015
 *      Author: collinm
 */

#include "buhlmannModel.h"
#include "constants.h"
#include "compartmentTissue.h"
#include "pressureSensor.h"
#include "ff.h"
#include "systemClock.h"

#include <array>
#include <math.h>
/**
        Schreiner Equation
        P=Palv+R∗(t−1/k)−(Palv−Pi−R/k)∗e^−k∗t
	
        Pi=Initial inert gas pressure in a tissue compartment. 
           The inert gas pressure value is fed recursively to the equation from start till end of a dive, 
           this is Pi=P after each dive step lasting t minutes.
           Fgas*(Pabs−Pwvp) 
    Palv=Pressure of inspired inert gas: Palv=Fgas*(Pabs−Pwvp)
        Pwvp=Water vapour pressure.
        Pabs=Absolute pressure of current depth [bar].
        Fgas=Inert gas fraction, i.e. 0.79 for air.
    t=Time of exposure in minutes.
        k=Gas decay constant for a tissue compartment: k=ln(2)/Thl
        Thl=Inert gas half-life time for tissue compartment.
        R=Rate of change of inert gas pressure: R=Fgas*Prate
 */
BuhlmannModel::BuhlmannModel() {

    //si fichier existe et qu'il y a des valeurs

    FRESULT fres;
    FIL f;

    fres = f_open(&f, "/tissues.txt", FA_WRITE | FA_OPEN_ALWAYS);
    if (fres) {
        char line[80];
        while (f_gets(line, sizeof line, &f)) {

        }

    } else {

        pressureSensor.capture_data();
        for (int i = 0; i < MAX_TISSUE; i++) {
            CompartmentTissue compartmentTissue = CompartmentTissue();
            compartmentTissue.ppN2 = GlobalConstants::NITROGEN_AIR * (pressureSensor.get_pressure_bar() - GlobalConstants::pressure_water);
            tissue[i] = compartmentTissue;
        }

    }

}

BuhlmannModel::~BuhlmannModel() {
    // TODO Auto-generated destructor stub
}

void BuhlmannModel::AscendDescend() {
    float k=0;
    //float t=
    float rate = pressureSensor.get_rate();
    float r = rate * GlobalConstants::NITROGEN_AIR;
    float current_pressure = pressureSensor.get_pressure_bar();
    float t = (current_pressure - pressureSensor.get_atm_pressure()) / rate;
    float palv = GlobalConstants::NITROGEN_AIR * (current_pressure - GlobalConstants::pressure_water);
    for (int i = 0; i < MAX_TISSUE; i++) {
        CompartmentTissue compartmentTissue = tissue[i];
        k=ln2/buehlmann_N2_t_halflife[i];
        
        compartmentTissue.ppN2 =  palv + r * (t - 1/k) - (palv - compartmentTissue.ppN2 - r / k ) * exp(-k*t);
        compartmentTissue.ppHe =  palv + r * (t - 1/k) - (palv - compartmentTissue.ppHe - r / k ) * exp(-k*t);
        tissue[i] = compartmentTissue;
        
    }
} 

void BuhlmannModel::ascentCeiling() {
    float maxAscentCeilling = 0;
    float tmpAscentCeilling = 0;
    for (int i = 0; i < MAX_TISSUE; i++) {
        float a = ((buehlmann_N2_a[i] * tissue[i].ppN2) + (buehlmann_He_a[i] * tissue[i].ppHe)) / (tissue[i].ppN2 + tissue[i].ppHe);
        float b = ((buehlmann_N2_b[i] * tissue[i].ppN2) + (buehlmann_He_b[i] * tissue[i].ppHe)) / (tissue[i].ppN2 + tissue[i].ppHe);
        tmpAscentCeilling = ((tissue[i].ppN2 + tissue[i].ppHe) - a) * b;

        if (tmpAscentCeilling > maxAscentCeilling) {

            maxAscentCeilling = tmpAscentCeilling;
        }
    }
}

float BuhlmannModel::Oxygen_toxicity_calculations() {

    return 1;
}

//http://scubatechphilippines.com/scuba_blog/decompression-theory-resources/
//https://www1.maths.leeds.ac.uk/~read/scuba/baker0.pdf
//ftp://www.decompression.org/pub/Wienke/deco.pdf
//http://www.frogkick.dk/library/deco/Erik%20Baker/ndl.pdf

float BuhlmannModel::NDL_calculation() {
    //t = (-1/k)*ln[(Pi - Mo)/(Pi - Po)]
    
    //ln x = loge x = y
    float min = -1;
    int k = 0;
    int t;
    for (int i = 0; i < MAX_TISSUE; i++) {
        double pi = (pressureSensor.get_pressure_bar() - GlobalConstants::pressure_water)* 2; //replace 2 by gaz value
        double mo = buehlmann_N2_a[i];
        double po = (pressureSensor.get_atm_pressure() - GlobalConstants::pressure_water) * GlobalConstants::NITROGEN_AIR;
        //do it only when Pi > Mo > Po
        if (pi > mo && mo > po) {
            k = ln2 / buehlmann_N2_t_halflife[i];
            t = (-1/k)*log((pi - mo)/(pi - po));

            if (t < min || min == -1) {
                min = t;
            }
        }
    }
    return min;
}



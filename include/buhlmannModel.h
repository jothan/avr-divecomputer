/*
 * BuhlmannModel.h
 *
 *  Created on: 24 févr. 2015
 *      Author: collinm
 */

#ifndef BUHLMANNMODEL_H_
#define BUHLMANNMODEL_H_


#include "compartmentTissue.h"
#include "math.h"
#include <array>

using namespace std;

class BuhlmannModel {
public:

    static const int MAX_TISSUE = 16;

    //buehlmann with 1b value
    const double buehlmann_He_t_halflife[MAX_TISSUE] = {1.88, 3.02, 4.72, 6.99, 10.21,
        14.48, 20.53, 29.11, 41.20, 55.19, 70.69, 90.34, 115.29, 147.42,
        188.24, 240.03};

    const float buehlmann_He_a[MAX_TISSUE] = {1.6189, 1.383, 1.1919, 1.0458, 0.922,
        0.8205, 0.7305, 0.6502, 0.595, 0.5545, 0.5333, 0.5189, 0.5181,
        0.5176, 0.5172, 0.5119};

    const float buehlmann_He_b[MAX_TISSUE] = {0.4770, 0.5747, 0.6527, 0.7223, 0.7582,
        0.7957, 0.8279, 0.8553, 0.8757, 0.8903, 0.8997, 0.9073, 0.9122,
        0.9171, 0.9217, 0.9267};

    //buehlmann with 1b value
    const float buehlmann_N2_t_halflife[MAX_TISSUE] = {5.0, 8.0, 12.5, 18.5, 27.0, 38.3,
        54.3, 77.0, 109.0, 146.0, 187.0, 239.0, 305.0, 390.0, 498.0, 635.0};

    const float buehlmann_N2_a[MAX_TISSUE] = {1.1696, 1.0, 0.8618, 0.7562, 0.62, 0.5043,
        0.441, 0.4, 0.375, 0.35, 0.3295, 0.3065, 0.2835, 0.261, 0.248,
        0.2327};

    const float buehlmann_N2_b[MAX_TISSUE] = {0.5578, 0.6514, 0.7222, 0.7825, 0.8126,
        0.8434, 0.8693, 0.8910, 0.9092, 0.9222, 0.9319, 0.9403, 0.9477,
        0.9544, 0.9602, 0.9653};

    const float buehlmann_N2_DeltaM[MAX_TISSUE] = {1.7928, 1.5352, 1.3847, 1.2780, 1.2306,
        1.1857, 1.1504, 1.1223, 1.0999, 1.0844, 1.0731, 1.0635, 1.0552, 1.0478, 1.0414, 1.0359};

    const float buelmann_N2_M0[MAX_TISSUE] = {2.9805146944, 2.5576038256, 2.26559394, 2.0440691992, 1.862821684, 1.7017127816, 1.6010197176, 1.5305345728, 1.4801880408, 1.4399108152, 1.409702896, 1.3794949768, 1.3492870576, 1.3190791384, 1.2989405256, 1.2788019128};

    array<CompartmentTissue, MAX_TISSUE> tissue;
    BuhlmannModel();
    virtual ~BuhlmannModel();
    void AscendDescend();
    void descent();
    void ascentCeiling();
    float NDL_calculation();
    float Oxygen_toxicity_calculations();
    float maximumOperationDepth();
private:
    float oldPressure;
    float currentPressure;
    const float ln2 = log(2);
    float getRQ();
};

extern BuhlmannModel buhlmannModel;

#endif /* BUHLMANNMODEL_H_ */

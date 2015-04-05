/*
 * BuhlmannModel.cpp
 *
 *  Created on: 24 févr. 2015
 *      Author: collinm
 */

#include "BuhlmannModel.h"
#include "Constants.h"
#include "CompartmentTissue.h"
#include <array>
#include "depth.h"
#include "ff.h"

BuhlmannModel::BuhlmannModel() {

    //si fichier existe et qu'il y a des valeurs

    FRESULT fres;
    FIL f;

    fres = f_open(&f, "/tissues.txt", FA_WRITE | FA_OPEN_ALWAYS);
    if (fres) {
        char line[80];
        while (f_gets(line, sizeof line, &f)){
            
        }
        
    } else {

        for (int i = 0; i < MAX_TISSUE; i++) {
            CompartmentTissue compartmentTissue = CompartmentTissue();
            compartmentTissue.ppN2 = GlobalConstants::NITROGEN_AIR * (depth.get_pressure_bar() - GlobalConstants::pressure_water);
            tissue[i] = compartmentTissue;
        }

    }

}

BuhlmannModel::~BuhlmannModel() {
    // TODO Auto-generated destructor stub
}

void BuhlmannModel::AscendDescend() {

}

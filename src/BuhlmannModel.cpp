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

BuhlmannModel::BuhlmannModel() {

	//si fichier existe et qu'il y a des valeurs
	if(1>2){
		int x = 2;
	}else{

		for (int i = 0; i < MAX_TISSUE; i++) {

			CompartmentTissue compartmentTissue = CompartmentTissue();
			//compartmentTissue.ppN2 = GlobalConstants::NITROGEN_AIR * (GlobalConstants::ambiant_pressure - GlobalConstants::pressure_water);

			tissue[i] = compartmentTissue;
		}

	}
	//sinon

}

BuhlmannModel::~BuhlmannModel() {
	// TODO Auto-generated destructor stub
}


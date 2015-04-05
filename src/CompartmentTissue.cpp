/*
 * CompartmentTissue.cpp
 *
 *  Created on: 24 févr. 2015
 *      Author: collinm
 */

#include "CompartmentTissue.h"

CompartmentTissue::CompartmentTissue() {
    kHe = 0;
    kN2 = 0; // Time constants - calculated from halftimes
    aHe = 0;
    bHe = 0;
    aN2 = 0;
    bN2 = 0; // A and b co-efficients
    ppHe = 0;
    ppN2 = 0;
}

CompartmentTissue::~CompartmentTissue() {
    // TODO Auto-generated destructor stub
}


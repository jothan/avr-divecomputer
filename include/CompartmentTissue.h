/*
 * CompartmentTissue.h
 *
 *  Created on: 24 févr. 2015
 *      Author: collinm
 */

#ifndef COMPARTMENTTISSUE_H_
#define COMPARTMENTTISSUE_H_

class CompartmentTissue {
public:
	float kHe, kN2;         // Time constants - calculated from halftimes
	float aHe, bHe, aN2, bN2; // A and b co-efficients
	float ppHe, ppN2;
	CompartmentTissue();
	virtual ~CompartmentTissue();
};

#endif /* COMPARTMENTTISSUE_H_ */

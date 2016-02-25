/*
* File:   Wheel.h
* Author: Daedalus
*
* Created on May 12, 2015
*/

#ifndef WHEEL_H
#define	WHEEL_H

#include "LFSR.h"

class Wheel {
	// Soft implementation of a contact wheel similar to those used
	// in the Enigma machine, but sized for an 8-bit space instead
	// of an alphabet.

	// Number of positions on each wheel.  Corresponds to the number
	// of possible values stored in a byte.  This value should always
	// be 256.
	const static int size = 256;

	// Array which contains the relation between the inputs and outputs.
	unsigned char contact[size];

	// Value of the position of the wheel, used to effect "rotating"
	// the contact wheel.
	unsigned char offset;

	// Boolean to track whether the wheel has been flipped.
	bool flipped;

	// Select an index and place the value at that index at the end
	// of the array, shifting all later values by one place.
	// Akin to pulling a card out of a deck and placing it on top.
	void Pull(unsigned char index);


public:

	// Setup the wheel by randomizing the values and offset, then 
	// inverting if necessary.
	void Setup(LFSR*, bool flag = false);

	// Empty constructor.  Necessary for implementation.
	Wheel();

	// Advance this wheel by the number specified.
	// Returns the number of rotations completed as a result
	// of this call to Tick().
	unsigned int Tick(unsigned int);

	// Process a single character through the wheel.
	unsigned char Scramble(unsigned char);

};

#endif	/* WHEEL_H */
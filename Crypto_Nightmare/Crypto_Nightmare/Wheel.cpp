/*
* File:   Wheel.cpp
* Author: Daedalus
*
* Created on May 12, 2015
*/

#include "Wheel.h"

void Wheel::Pull(unsigned char index) {

	// Remove the value at the spacified index and append it to the end of the array

	unsigned char temp = contact[index];		// Setup a temporary variable for picked value.

	for (int i = index; i < size - 1; i++) {	// Shift the whole array down.
		contact[i] = contact[i + 1];
	}

	contact[size - 1] = temp;					// Place picked value at end of array.

}

void Wheel::Setup(LFSR * gen, bool flag) {

	// Prepares the wheel for use by randomizing the array and offset.
	// Inverts indeces with stored values so that the same algorithm works for
	// both encryption and decryption, and similar processing times are achieved.

	for (int i = 0; i < size; i++) {			// Fill the array with the set of values
												// between 0 and 255, inclusive.
		contact[i] = i;

	}

	for (int i = 0; i < size * 10; i++) {		// Randomize wheel by pullng values.

		Pull(gen->NextChar());

	}

	offset = gen->NextChar();					// Generate a random offset/

	flipped = flag;								// Set the flag to indicate whether the
												// wheel has been flipped.

	if (flipped) {
		// If the array needs to be flipped, flip it

		unsigned char temp[size];				// Set up a temporary array

		for (int i = 0; i < size; i++) {

			temp[contact[i]] = (unsigned char)i;// Assign the values to their new 
												// position in the temporary array.

		}

		for (int i = 0; i < size; i++) {

			contact[i] = temp[i];				// Move the new array into this wheel's field.

		}

	}

}

Wheel::Wheel() {}  // Empty constructor.  Call Setup() after instance is declared.

unsigned int Wheel::Tick(unsigned int count) {

	// Advance the wheel by increasing the offset and returning the number of complete
	// rotations that have been completed.

	unsigned int carry = (offset + count) / size;

	offset += count;

	return carry;
}

unsigned char Wheel::Scramble(unsigned char input) {

	// Process a single character through this wheel.

	unsigned char out = 0;

	if (flipped) {

		out = contact[input] - offset;

	}
	else {

		out = contact[input += offset];

	}

	return out;
}
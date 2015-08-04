/*
* File:   Enigma.h
* Author: Daedalus
*
* Created on May 13, 2015
*/

#ifndef ENIGMA_H
#define	ENIGMA_H

#include <list>
#include "LFSR.h"
#include "Wheel.h"

class Enigma {
	// Software implementation of a multi-rotor encryption device,
	// similar to the Enigma Machine.

	// Random number generator used to randomize the wheels.
	LFSR gen;

	// Number of rotors to be used.
	const static int numrotors = 5;

	// Array to contain the contact wheels.
	Wheel rotor[numrotors];

	// boolean to track whether the system has been flipped.
	bool flipped;

	// Advance the first rotor by the specified value and propagate
	// the rotations along all rotors as necessary.
	void Tick(unsigned int);

public:

	// Publicly accessable value for the bit size of the LFSR
	const static int size = 256;

	// Constructor to setup the rotors and flip them if necessary.
	Enigma();

	int Setup(char*, bool flag = false, int init_offset = 0);

	// Process a list of type char.
	void Process(std::list<unsigned char>*);

};

#endif	/* ENIGMA_H */
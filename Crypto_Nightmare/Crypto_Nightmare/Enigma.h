/*
* File:   Enigma.h
* Author: Daedalus
*
* Created on May 13, 2015
*/

#ifndef ENIGMA_H
#define	ENIGMA_H

#include "LFSR.h"
#include "Wheel.h"

class Enigma {

	LFSR gen;

	const static int numrotors = 5;

	Wheel rotor[numrotors];

	bool flipped;

	void Tick(unsigned int);

public:

	const static int size = 256;

	Enigma(char[], bool flag = false);

	void Process(unsigned char *, int);

};

#endif	/* ENIGMA_H */
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

	const static int size = 256;
	unsigned char contact[size];

	unsigned char offset;

	bool flipped;

	void Pull(unsigned char index);


public:

	void Setup(LFSR*, bool flag = false);
	Wheel();

	unsigned int Tick(unsigned int);

	unsigned char Scramble(unsigned char);

};

#endif	/* WHEEL_H */
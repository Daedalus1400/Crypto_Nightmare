/*
* File:   Wheel.cpp
* Author: Daedalus
*
* Created on May 12, 2015
*/

#include "Wheel.h"

void Wheel::Pull(unsigned char index) {

	unsigned char temp = contact[index];

	for (int i = index; i < size - 1; i++) {
		contact[i] = contact[i + 1];
	}

	contact[size - 1] = temp;

}

void Wheel::Setup(LFSR * gen, bool flag) {

	for (int i = 0; i < size; i++) {

		contact[i] = i;

	}

	for (int i = 0; i < size * 10; i++) {

		Pull(gen->NextChar());

	}

	offset = gen->NextChar();

	flipped = flag;

	if (flipped) {

		unsigned char temp[size];

		for (int i = 0; i < size; i++) {

			temp[contact[i]] = (unsigned char)i;

		}

		for (int i = 0; i < size; i++) {

			contact[i] = temp[i];

		}

	}

}

Wheel::Wheel() {}

unsigned int Wheel::Tick(unsigned int count) {

	unsigned int carry = (offset + count) / size;

	offset += count;

	return carry;
}

unsigned char Wheel::Scramble(unsigned char input) {

	unsigned char out = 0;

	if (flipped) {

		out = contact[input] - offset;

	}
	else {

		input += offset;

		out = contact[input];

	}

	return out;
}
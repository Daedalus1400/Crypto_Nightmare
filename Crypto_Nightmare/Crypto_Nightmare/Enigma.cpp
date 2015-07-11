/*
* File:    Enigma.cpp
* Author:  Daedalus
*
* Created on May 13, 2015
*/

#include "Enigma.h"

Enigma::Enigma(char* input, bool flag) {

	flipped = flag;

	gen.Setup(input);

	for (int i = 0; i < numrotors; i++) {

		rotor[i].Setup(&gen, flipped);

	}

}

void Enigma::Tick(unsigned int count) {

	for (int i = 0; i < numrotors; i++) {

		if (count == 0) {

			return;

		}

		count = rotor[i].Tick(count);

	}

}

void Enigma::Process(unsigned char * buffer, int filesize) {

	if (!flipped) {

		unsigned char temp;

		for (int i = 0; i < filesize; i++) {

			temp = buffer[i];

			for (int j = 0; j < numrotors; j++) {

				buffer[i] = rotor[j].Scramble(buffer[i]);

			}

			Tick(temp);

		}

	}
	else {

		for (int i = 0; i < filesize; i++) {

			for (int j = numrotors - 1; j > -1; j--) {

				buffer[i] = rotor[j].Scramble(buffer[i]);

			}

			Tick(buffer[i]);

		}

	}

}
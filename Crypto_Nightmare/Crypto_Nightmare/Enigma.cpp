/*
* File:    Enigma.cpp
* Author:  Daedalus
*
* Created on May 13, 2015
*/

#include "Enigma.h"

Enigma::Enigma() {
	// Constructor to setup the rotors
}

int Enigma::Setup(char* input, bool flag, int init_offset) {

	flipped = flag;

	if (!gen.Setup(input)) {							// Setup the PRNG.

		return 1;

	}

	for (int i = 0; i < numrotors; i++) {

		rotor[i].Setup(&gen, flipped);			// Setup the rotors with the LFSR.

	}

	Tick(init_offset);

	return 0;

}

void Enigma::Tick(unsigned int count) {

	// Advance the first rotor by the specified amount and propagate through
	// the other rotors as necessary.
	for (int i = 0; i < numrotors; i++) {

		if (count == 0) {						// If the next rotor would not advance,

			return;								// exit the loop early.

		}

		count = rotor[i].Tick(count);			// Advance the current rotor and store
												// the number of times the next rotor
	}											// must advance.

}

void Enigma::Process(std::list<unsigned char>* buffer) {
	// Process all of the char's in the buffer array with given size.

	int size = buffer->size();

	if (flipped) {								// If decrypting the array

		std::list<unsigned char>::iterator it = buffer->begin();

		for (int i = 0; i < size; i++) {
			// For each char

			for (int j = numrotors - 1; j > -1; j--) {
				// For each rotor

				*it = rotor[j].Scramble(*it); // Process the char.

			}

			Tick(*it + 1);		// Advance the first rotor by the numerical value of
								// the plaintext char that was just processed.
			it++;
			}

	}
	else {										// If encrypting the array

		unsigned char temp;						// Initialize a temporary variable.

		std::list<unsigned char>::iterator it = buffer->begin();

		for (int i = 0; i < size; i++) {
			// For each char

			temp = *it + 1;						// Assign the plaintext value to temp.

			for (int j = 0; j < numrotors; j++) {
				// for each rotor

				*it = rotor[j].Scramble(*it);	//Process the char.

			}

			Tick(temp);			// Advance the first rotor by the numerical value of
								// the plaintext char that was just procesed.
			it++;
		}

	}

}
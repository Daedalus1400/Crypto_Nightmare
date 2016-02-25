/*
* File:   LFSR.cpp
* Author: Daedalus
*
* Created on May 5, 2015
*/

#include "LFSR.h"
#include <math.h>

bool LFSR::Setup(char* start) {

	// Initialize the Linear Feedback Shift Register by selecting tap locations
	// and setting the initial state.

	for (int i = 0; i < length / 8; i++) {

		state.c[i] = start[i];					// Move the input to this instance's field

	}

	Sieve();									// Generate a list of prime numbers.
												// Stored in a field.

	tap[0].bit = length - 1;					// The first tap is the last bit

	tap[1].bit = primes[state.s[0] % numprimes] - 1;// The second tap is a randomly chosen
												// prime numbered bit.  This ensures
												// coprimality between the taps.

	int j = 1;									// Helper variable to track which chunk
												// of the input to use to select taps 3+4.

	// Selection of the third tap.

	tap[2].bit = -1;							// Initialize tap 3 to a specific invalid value

	while (tap[2].bit == -1) {

		tap[2].bit = (state.s[j] % length) - 1;// Assign the value to tap 3

		if (tap[2].bit == tap[1].bit) {			// If tap 3 == tap 2,
			tap[2].bit = -1;					// put tap 3 back to its specific invalid value
		}										// causing the loop to repeat and try again.

		j++;									// Change the section of the input to use

		if (j >= length / 16) {					// If j is out of range of the input
			return false;						// return false to indicate an error.
		}

	}

	// Selection of the fourth and final tap.  Identical to above except that it
	// checks both taps 2 and 3 for repetition.

	tap[3].bit = -1;								

	while (tap[3].bit == -1) {

		tap[3].bit = (state.s[j] % 256) - 1;

		if (tap[3].bit == tap[1].bit || tap[3].bit == tap[2].bit) {
			tap[3].bit = -1;
		}

		j++;

		if (j >= length / 16) {
			return false;
		}

	}

	SetupTaps();								// Calculate which place in which byte
												// each tap is located.

	return true;								// Return true upon successful completion.

}

LFSR::LFSR() {}  // Empty constructor.  Call Setup() after instantiation instead.

void LFSR::SetupTaps() {

	for (int i = 0; i < numtaps; i++) {
		tap[i].byte = tap[i].bit / 8;
		tap[i].place = tap[i].bit % 8;
	}

}

bool LFSR::ReadBit(unsigned char target, int pos) {
	// Reads the specified bit of the specified char.
	// pos of 0 is the highest significant bit (leftmost).
	unsigned char mask = 1 << (7 - pos);		// Create bit mask

	return target & mask;						// Return result of AND with bitmask
}

bool LFSR::ReadBit(unsigned long target, int pos) {
	// Overload of the above method for long type integers.
	// pos of 0 is the highest significant bit (leftmost).
	unsigned long mask = 1 << (63 - pos);		// Create bit mask

	return target & mask;						// Return result of AND with bitmask
}

void LFSR::SetBit(unsigned char * target, int pos, bool val) {
	// Sets the specified bit of the specified char.
	// pos of 0 is the highest significant bit (leftmost).
	if (val == ReadBit(*target, pos)) {			// If the bit is already the desired value,
		return;									// return without changing anything,
	}
	else {										// otherwise change it by XORing a 1 at
		*target ^= (1 << ((sizeof(*target) * 8 - 1) - pos));// the correct location
	}
}

void LFSR::SetBit(unsigned long * target, int pos, bool val) {
	// Overload of the above method for long type integers.
	// pos of 0 is the highest significant bit (leftmost).
	if (val == ReadBit(*target, pos)) {
		return;
	}
	else {
		*target ^= (1 << ((sizeof(*target) * 8 - 1) - pos));
	}
}

bool LFSR::Clock() {

	bool out[numtaps];							// Initialize an array to hold the output 
												// values from the tap locations.

	for (int i = 0; i < numtaps; i++) {
		// Put the value at each tap into the output array.
		out[i] = ReadBit(state.c[tap[i].byte], tap[i].place);

	}

	bool funcout = out[0];						// Initialize the output from the XOR
												// operations.

	for (int i = 1; i < numtaps; i++) {
		// XOR each tap's value to the result of the previous XOR operation.
		funcout ^= out[i];

	}

	bool carry[length / 64];					// Initialize an array to hold the values
												// that would be lost in shifting the 
												// register due to the size of the
												// containing long data types.

	carry[0] = funcout;							// The first long gets the feedback bit.

	for (int i = 0; i < (length / 64 - 1); i++) {
		// Each long gets the least significant bit of the preavious long
		carry[i + 1] = ReadBit(state.l[i], sizeof(state.l[i]) - 1);

	}

	for (int i = 0; i < (length / 64); i++) {
		// Shift each long and put the carry bit into its most significant bit.
		state.l[i] >>= 1;
		SetBit(&state.l[i], 0, carry[i]);

	}

	return funcout;								// Return the output bit as a boolean.
}

unsigned char LFSR::NextChar() {

	// Generate 8 psudorandom bits and put them into an unsigned char type

	unsigned char out = 0;

	for (int i = 0; i < 8; i++) {
		out ^= (Clock() << i);
	}
	return out;
}

void LFSR::Sieve() {

	// Generate a list of prime numbers less than the number of positions in the shift register.

	for (int i = 0; i < length + 1; i++) {

		primes[i] = i;							// Initialize the array with all possible values.

	}

	primes[0] = -1;								// Zero is not prime by definition.

	primes[1] = -1;								// One is not prime by definition.

	for (int i = 2; i <= int(sqrt((double)length)); i++) {
		// Go through the list and remove any number that is a multiple of any currently known
		// prime.  The system only knows 2 to be prime initially.

		if (primes[i] != -1) {					// If the current value is prime,

			for (int j = 2; j <= length / i; j++) {

				primes[i*j] = -1;				// remove all multiples less than length.

			}

		}

	}

	numprimes = 0;								// Initialize helper variable to count primes.

	for (int i = 0; i < length + 1; i++) {
		// Count the number of known primes in the array.
		if (primes[i] != -1) {

			numprimes++;

		}

	}

	int j = 0;									// Initialize helper variable to track write
												// position in the array.

	for (int i = 0; i < length + 1; i++) {

		if (primes[i] != -1) {

			primes[j++] = primes[i];			// Move primes to be consecutive at the 
												// begining of the array for easy access.
		}

	}

}
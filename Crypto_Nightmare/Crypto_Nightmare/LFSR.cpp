/*
* File:   LFSR.cpp
* Author: Daedalus
*
* Created on May 5, 2015
*/

#include "LFSR.h"
#include <math.h>

bool LFSR::Setup(char* start) {

	for (int i = 0; i < length / 8; i++) {

		state.c[i] = start[i];

	}

	Sieve();

	taps[0] = length - 1;
	taps[1] = primes[state.c[0] % numprimes] - 1;

	int j = 1;

	for (int i = 2; i < numtaps; i++) {

		taps[i] = int(state.c[j - 1]) % (length - 1);

	}

	return true;

}

LFSR::LFSR() {}

bool LFSR::ReadBit(unsigned char * target, int pos) {
	unsigned char temp = *target << pos;
	temp >>= 7;
	if (temp == 1) {
		return true;
	}
	else {
		return false;
	}
}

bool LFSR::ReadBit(unsigned long * target, int pos) {
	unsigned long temp = *target << pos;
	temp >>= (sizeof(temp) * 8 - 1);
	if (temp == 1) {
		return true;
	}
	else {
		return false;
	}
}

void LFSR::SetBit(unsigned char * target, int pos, bool val) {
	if (val == ReadBit(target, pos)) {
		return;
	}
	else {
		*target ^= (1 << (7 - pos));
	}
}

void LFSR::SetBit(unsigned long * target, int pos, bool val) {
	if (val == ReadBit(target, pos)) {
		return;
	}
	else {
		*target ^= (1 << (63 - pos));
	}
}

bool LFSR::Clock() {

	bool out[numtaps];

	for (int i = 0; i < numtaps; i++) {

		int byte = taps[i] / 8;
		int place = taps[i] % 8;
		unsigned char * point = &state.c[byte];
		out[i] = ReadBit(point, place);

	}

	bool funcout = out[0];

	for (int i = 1; i < numtaps; i++) {

		funcout ^= out[i];

	}

	bool carry[length / 64];

	carry[0] = funcout;

	for (int i = 0; i < (length / 64 - 1); i++) {

		unsigned long * point = &state.l[i];
		carry[i + 1] = ReadBit(point, 63);

	}

	for (int i = 0; i < (length / 64); i++) {

		state.l[i] >>= 1;
		unsigned long * point = &state.l[i];
		SetBit(point, 0, carry[i]);

	}

	return funcout;
}

unsigned char LFSR::NextChar() {

	unsigned char out;

	for (int i = 0; i < 8; i++) {
		out ^= (Clock() << i);
	}
	return out;
}

void LFSR::Sieve() {

	for (int i = 0; i < length + 1; i++) {

		primes[i] = i;

	}

	primes[0] = -1;
	primes[1] = -1;

	for (int i = 2; i <= int(sqrt((float)length)); i++) {

		if (primes[i] != -1) {

			for (int j = 2; j <= length / i; j++) {

				primes[i*j] = -1;

			}

		}

	}

	numprimes = 0;

	for (int i = 0; i < length + 1; i++) {

		if (primes[i] != -1) {

			numprimes++;

		}

	}

	int j = 0;

	for (int i = 0; i < length + 1; i++) {

		if (primes[i] != -1) {

			primes[j++] = primes[i];

		}

	}

}
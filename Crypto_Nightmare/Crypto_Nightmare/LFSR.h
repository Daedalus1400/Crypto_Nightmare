/*
* File:   LFSR.h
* Author: Daedalus
*
* Created on May 5, 2015
*/

#ifndef LFSR_H
#define	LFSR_H

class LFSR {

	const static int length = 256;
	const static int numtaps = 4;

	int primes[length + 1];
	int numprimes;


	union internal {
		unsigned long l[length / 64];
		unsigned char c[length / 8];
	} state;

	int taps[numtaps];

	void SetBit(unsigned char*, int, bool);
	void SetBit(unsigned long*, int, bool);

	bool ReadBit(unsigned char*, int);
	bool ReadBit(unsigned long*, int);

	bool Clock();

	void Sieve();

public:

	bool Setup(char*);
	LFSR();

	unsigned char NextChar();

};

#endif	/* LFSR_H */
/*
* File:   ThreadedEnigma.h
* Author: Daedalus
*
* Created on July 19, 2015
*/

#ifndef THREADEDENIGMA_H
#define THREADEDENIGMA_H

#include "Enigma.h"
#include <iostream>
#include <thread>
#include <vector>

class ThreadedEnigma {

	int chunk_size;

	struct threadPiece {
		Enigma * enigma;
		byte * start;
		unsigned int length;
	};

	std::vector<threadPiece*> piece;
	std::vector<std::thread*> threads;

	static void ProcessPiece(threadPiece *);

public:

	ThreadedEnigma();

	int Process(std::vector<byte> *, char*, bool flag = false, unsigned int thread_count = 0);
	
};

#endif /* THREADEDENIGMA_H */
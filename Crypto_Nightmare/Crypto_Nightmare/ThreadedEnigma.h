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
#include <list>

class ThreadedEnigma {

	int chunk_size;

	struct threadPiece {
		Enigma * enigma;
		std::list<unsigned char> * chunk;
	};

	std::list<threadPiece*> piece;
	std::list<std::thread*> threads;

	static void ProcessPiece(threadPiece *);

public:

	ThreadedEnigma();

	int Process(std::list<unsigned char> *, char*, bool flag = false, unsigned int thread_count = 0);
	
};

#endif /* THREADEDENIGMA_H */
/*
* File:    ThreadedEnigma.cpp
* Author:  Daedalus
*
* Created on July 19, 2015
*/

#include "ThreadedEnigma.h"

ThreadedEnigma::ThreadedEnigma() {}

int ThreadedEnigma::Process(std::vector<unsigned char> * buffer, char * password, bool flag, unsigned int thread_count) {

	// Establish number of threads

	if (thread_count == 0) {
		// If unassigned, use the number of cores returned by the OS
		thread_count = std::thread::hardware_concurrency();

	}

	if (thread_count == 0 || flag) {
		// If OS thread count returns zero, only use 1 thread.
		// Or if decrypting, use only 1 thread.
		thread_count = 1;
	}
	
	chunk_size = buffer->size()/thread_count;

	std::cout << "\nUsing " << thread_count << " threads.\n\n";
	std::cout << buffer->size() << " bytes in total.\n\n";
	std::cout << "Approximately " << chunk_size << " bytes per thread.\n\n";
	
	// Setup each thread's Enigma and break up the buffer into sections

	
	unsigned long sum = 0;
	byte * it = &(*buffer)[0];

	for (unsigned int i = 1; i < thread_count; i++) {

		threadPiece * p = new  threadPiece;

		p->start = it;

		Enigma * e = new Enigma();

		if (e->Setup(password, flag, sum) == 1) {
			return 1;
		}

		p->enigma = e;
		p->length = chunk_size;

		piece.push_back(p);

		for (int j = 0; j < chunk_size; j++) {

			sum += (*it+1);
			it++;

		}
	}

	// Set up the last threadPiece

	threadPiece * p = new threadPiece;

	p->start = it;

	Enigma * e = new Enigma();

	e->Setup(password, flag, sum);

	p->enigma = e;

	p->length = buffer->size() - (thread_count - 1) * chunk_size;

	piece.push_back(p);
	
	// Set each thread running
	
	int i = 0;
	for (threadPiece * tp : piece) {

		std::thread * thread = new std::thread(&ProcessPiece, tp);

		threads.push_back(thread);
		//std::cout << "Thread " << i++ << " has started.\n";
	}

	// Wait for all the threads to finish
	i = 0;
	std::cout << std::endl;
	for (std::thread * t : threads) {
		
		t->join();
		//std::cout << "Thread " << i++ << " has finished.\n";
	}

	// Clear internal memory

	for (threadPiece * p : piece) {
		delete p;
	}

	piece.clear();
	threads.clear();
	
	return 0;
}

void ThreadedEnigma::ProcessPiece(threadPiece * input) {

	input->enigma->Process(input->start, input->length);

}
/*
* File:   FileHandler.cpp
* Author: Daedalus
*
* Created on August 23, 2015
*/

#include "FileHandler.h"

int GetFile(char * file, std::vector<byte> * buffer) {

	std::fstream * fs = new std::fstream;

	fs->open(file, std::fstream::in | std::fstream::binary);
	
	if (!fs->good()) {
		std::cout << "File was not opened.\n";
		return 1;

	}

	buffer->clear();

	while (fs->peek() != std::char_traits<byte>::eof()) {
		buffer->push_back(fs->get());
	}

	if (fs->is_open()) {
		fs->close();
	}

	return 0;
}

int WriteFile(char * file, std::vector<byte> * buffer) {

	std::fstream * fs = new std::fstream;

	fs->open(file, std::fstream::out | std::fstream::trunc | std::fstream::binary);

	if (!fs->good()) {
		std::cout << "File was not opened.\n";
		return 1;
	}

	for (int i = 0; i < buffer->size(); i++) {
		fs->put(buffer->at(i));
	}

	if (fs->is_open()) {
		fs->close();
	}

	return 0;
}
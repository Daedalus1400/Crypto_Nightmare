/*
* File:   FileHandler.h
* Author: Daedalus
*
* Created on August 23, 2015
*/

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <vector>
#include <iostream>

typedef unsigned char byte;

	int GetFile(char*, std::vector<byte>*);
	int WriteFile(char*, std::vector<byte>*);

#endif // !FILEHANDLER_H

/*
* File:   main.cpp
* Author: Daedalus
*
* Created on May 5, 2015
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <thread>
#include "ThreadedEnigma.h"
#include "Timer.h"
#include "FileHandler.h"

using namespace std;

void PrintfromVector(vector<byte>);

int main() {

	Timer * time = new Timer();

	char password[] = "Arbitrary password for no reason";

	vector<byte> * buffer = new vector<byte>;

	GetFile("testimage", buffer);

	ThreadedEnigma * cypher = new ThreadedEnigma();

	cypher->Process(buffer, password, true, 8);

	WriteFile("outimage", buffer);

	//time->Delayms(5000);

	return 0;

}

void PrintfromVector(vector<byte> text) {

	for (char c : text) {
		cout << c;
	}

}
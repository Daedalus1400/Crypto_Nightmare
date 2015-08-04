/*
* File:   main.cpp
* Author: Daedalus
*
* Created on May 5, 2015
*/

#include <cstdlib>
#include <iostream>
#include <list>
#include <thread>
#include "ThreadedEnigma.h"
#include "Enigma.h"
#include "Timer.h"

using namespace std;

void PrintfromList(list<unsigned char>);

int main() {

	Timer * time = new Timer();

	unsigned char text[] = "This is a very long string of plaintext, to be used for tests.";

	list<unsigned char> input;

	for (unsigned char c : text) {

		input.push_back(c);

	}

	char phrase[128];
	cout << "Hardware Concurrency: " << thread::hardware_concurrency() << " threads\n";
	cout << "Passphrase?\n>";
	cin >> phrase;
	
	Enigma * forward = new Enigma();
	Enigma * backward = new Enigma();

	forward->Setup(phrase);
	backward->Setup(phrase, true);
	

	ThreadedEnigma * cypher = new ThreadedEnigma();
	
	PrintfromList(input);
	cout << endl;

	forward->Process(&input);
	//cypher->Process(&input, phrase, false, 4);

	PrintfromList(input);
	cout << endl;

	backward->Process(&input);
	//cypher->Process(&input, phrase, true, 4);

	PrintfromList(input);
	cout << endl;

	time->Delayms(10000);

	return 0;

}

void PrintfromList(list<unsigned char> text) {

	for (unsigned char& c : text) {
		cout << c;
	}

}
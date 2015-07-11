/*
* File:   main.cpp
* Author: Daedalus
*
* Created on May 5, 2015
*/

#include <cstdlib>
#include <iostream>
#include "Enigma.h"
#include "Timer.h"

using namespace std;

int main() {

	Timer * time = new Timer();

	char phrase[33];

	cout << "Passphrase?\n>";
	cin >> phrase;

	Enigma forward(phrase);
	Enigma backward(phrase, true);

	time->Delayms(3000);

	return 0;

}
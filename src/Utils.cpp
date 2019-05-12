/*
 * Utils.cpp
 *
 *  Created on: May 12, 2019
 *      Author: anuwat
 */
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

#include "Utils.h"

static const int IGNORE_CHARS = 256;

char GetCharacter(const char * prompt, const char * error) {

	char input;
	bool failure;

	do {
		failure = false;
		cout << prompt;

		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;

		} else {
			cin.ignore(IGNORE_CHARS, '\n');
			if (isalpha(input)) {
				input = tolower(input);

			} else {
				cout << error << endl;
				failure = true;
			}
		}

	} while (failure);

	return input;

}

char GetCharacter(const char * prompt, const char * error,
		const char validInput[], int validInputLen) {

	char input;
	bool failure;

	do {
		failure = false;
		cout << prompt;

		cin >> input;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << error << endl;
			failure = true;

		} else {
			cin.ignore(IGNORE_CHARS, '\n');
			if (isalpha(input)) {
				input = tolower(input);

				for (int i = 0; i < validInputLen; i++) {
					if (input == validInput[i]) {
						return input;
					}
				}

			}
			cout << error << endl;
			failure = true;

		}

	} while (failure);

	return input;

}

void ClearScreen() {
	system("cls");
}


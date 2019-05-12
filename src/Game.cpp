/*
 * Game.cpp
 *
 *  Created on: May 12, 2019
 *      Author: anuwat
 */

#include "Game.h"
#include "Utils.h"
static const char * INPUT_ERROR_STRING = "Input error! Please try again.";
static const char * PLS_INPUT_SECRET_MSG = "Please enter the secret phrase: ";
static const char * YOU_MUST_ENTER_THE_WORD = "You must enter the word.";
static const char * PLAY_AGAIN_MSG = "Would you like to play again (y/n) : ";
static const char * PLS_INPUT_GUESS = "Please input your guess: ";

static const int IGNORE_CHARS = 256;

void PlayGame() {

	const int MAX_LEN_SECRET_PHRASE = 256;
	const int MAX_NUMBER_OF_GUESS = 6;

	char secretPhrase[MAX_LEN_SECRET_PHRASE];
	char * optrHiddenPhase = nullptr;
	int numberOfGuessLeft = MAX_NUMBER_OF_GUESS;
	int secretPhraseLen = GetSecretPhrase(secretPhrase, MAX_LEN_SECRET_PHRASE);
	optrHiddenPhase = MakeHiddenPhrase(secretPhrase, secretPhraseLen);

	DrawBoard(numberOfGuessLeft, optrHiddenPhase);

	char guess;
	do {
		guess = GetGuess();

		UpdateBoard(guess, optrHiddenPhase, secretPhrase, secretPhraseLen,
				numberOfGuessLeft);

		DrawBoard(numberOfGuessLeft, optrHiddenPhase);

	} while (!IsGameOver(numberOfGuessLeft, optrHiddenPhase, secretPhraseLen));

	DisplayResult(secretPhrase, numberOfGuessLeft);

	delete[] optrHiddenPhase;
	optrHiddenPhase = nullptr;

}

int GetSecretPhrase(char secretPhrase[], int maxSecretPhraseLen) {
	bool failure;
	int inputLen;
	do {
		failure = false;
		cout << PLS_INPUT_SECRET_MSG;
		cin.get(secretPhrase, maxSecretPhraseLen);

		if (cin.fail()) {
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << INPUT_ERROR_STRING << endl;
			failure = true;
		} else {
			inputLen = strlen(secretPhrase);

			if (inputLen == 0) {
				cout << YOU_MUST_ENTER_THE_WORD << endl;
				failure = true;
			}
		}

	} while (failure);

	return inputLen;

}

char * MakeHiddenPhrase(const char * secretPhrase, int secretPhraseLen) {
	char * hiddenPhrase = new char[secretPhraseLen + 1];

	for (int i = 0; i < secretPhraseLen; i++) {
		if (secretPhrase[i] != ' ') {
			hiddenPhrase[i] = '-';
		} else {
			hiddenPhrase[i] = ' ';
		}
	}
	hiddenPhrase[secretPhraseLen] = '\0';
	return hiddenPhrase;

}

void DrawBoard(int numberOfGuessLeft, const char * noptrHiddenPhase) {
	ClearScreen();
	switch (numberOfGuessLeft) {
	case 0: {
		DRAW(" +---+");
		DRAW(" |   |");
		DRAW(" |   O");
		DRAW(" |  /|\\");
		DRAW(" |  / \\");
		DRAW_END_LINE("-+-");
	}
		break;
	case 1: {
		DRAW(" +---+");
		DRAW(" |   |");
		DRAW(" |   O");
		DRAW(" |  /|\\");
		DRAW(" |  /");
		DRAW_END_LINE("-+-");
	}
		break;
	case 2: {
		DRAW(" +---+");
		DRAW(" |   |");
		DRAW(" |   O");
		DRAW(" |  /|\\");
		DRAW(" |");
		DRAW_END_LINE("-+-");
	}
		break;
	case 3: {
		DRAW(" +---+");
		DRAW(" |   |");
		DRAW(" |   O");
		DRAW(" |  /|");
		DRAW(" |");
		DRAW_END_LINE("-+-");
	}
		break;
	case 4: {
		DRAW(" +---+");
		DRAW(" |   |");
		DRAW(" |   O");
		DRAW(" |   |");
		DRAW(" |");
		DRAW_END_LINE("-+-");
	}
		break;
	case 5: {
		DRAW(" +---+");
		DRAW(" |   |");
		DRAW(" |   O");
		DRAW(" |   ");
		DRAW(" |");
		DRAW_END_LINE("-+-");
	}
		break;
	case 6: {
		DRAW(" +---+");
		DRAW(" |   |");
		DRAW(" |   ");
		DRAW(" |   ");
		DRAW(" |");
		DRAW_END_LINE("-+-");
	}
		break;
	default:
		break;

	}
	cout << "Secret phrase is : " << noptrHiddenPhase << endl << endl;
}





char GetGuess() {
	return GetCharacter(PLS_INPUT_GUESS, INPUT_ERROR_STRING);
}

void UpdateBoard(char guess, char * noptrHiddenPhase, const char secretPhrase[],
		int secretPhraseLen, int & numberOfGuessLeft) {

	bool found = false;

	for (int i = 0; i < secretPhraseLen; i++) {
		if (tolower(secretPhrase[i]) == guess) {
			noptrHiddenPhase[i] = secretPhrase[i];
			found = true;
		}
	}

	if (!found) {
		numberOfGuessLeft--;
	}

}

bool IsGameOver(int numberOfGuessLeft, const char * optrHiddenPhase,
		int secretPhraseLen) {

	bool hasDash = false;
	for (int i = 0; i < secretPhraseLen; i++) {
		if (optrHiddenPhase[i] == '-') {
			hasDash = true;
			break;
		}
	}
	return numberOfGuessLeft == 0 || !hasDash;
}

bool WantToPlayAgain() {

	const char validInput[] = { 'y', 'n' };

	char response = GetCharacter(PLAY_AGAIN_MSG, INPUT_ERROR_STRING, validInput,
			2);

	return response == 'y';

}

void DisplayResult(const char * secretPhrase, int numberOfGuessLeft) {

	if (numberOfGuessLeft > 0) {
		cout << "You got it! The phrase was: " << secretPhrase << endl;
	} else {
		cout << "You didn't get it ! The phrase was: " << secretPhrase << endl;
	}

}



/*
 * Utils.h
 *
 *  Created on: May 12, 2019
 *      Author: anuwat
 */

#ifndef UTILS_H_
#define UTILS_H_


char GetCharacter(const char * prompt, const char * error,
		const char validInput[], int validInputLen);
char GetCharacter(const char * prompt, const char * error);

void ClearScreen();

#endif /* UTILS_H_ */

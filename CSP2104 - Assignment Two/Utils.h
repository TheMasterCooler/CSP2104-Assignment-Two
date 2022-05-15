#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

namespace utils {
	std::vector<std::string> stringExplode(std::string content, std::string delimeter);
	std::string readFile(const char* filePath);
	std::string toLower(std::string);

	/*
	* Provides a safe method of retrieving input from the user. Protects against
	* overflows and bad bits.
	*
	* Param(s):
	*	prompt (std::string) - The prompt to display before the data entry.
	* Return:
	*	input - Automatically assigning type, value entered by user.
	* Author:
	*	Ben Armstrong (10547876) - 14/03/2022
	* Notes:
	*	This is pretty nice. I tried to make it work with pointers, however had
	*	multiple issues. 100% my fault. Please see link below for "inspiration"
	*	https://stackoverflow.com/questions/13212043/loop-until-integer-input-is-in-required-range-fails-to-work-with-non-digit-chara
	*/
	// Create a template, this will auto adapt to the type entered at function execution
	template<class input>
	input getInput(std::string prompt) {
		input userInput;

		// Prompt the user and define a holding variable
		std::cout << prompt;
		std::string line;
		// Indefinitely read user input until something valid is entered
		while (std::getline(std::cin, line)) {
			std::stringstream linestream(line);
			// Is it the right type, if incorrect prompt user and retry
			if (!(linestream >> userInput)) {
				std::cout << "Invalid input entered. Please try again.\n";
				std::cout << prompt;
				continue;
			}
			break;
		}
		return userInput;
	}
}
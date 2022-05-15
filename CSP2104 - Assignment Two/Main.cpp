#include "Utils.h"
#include "Word.h"
#include "Dictionary.h"

#include <iostream>

#define DICTIONARY "dictionary2022_S1.txt" // The dictionary file name, shouldn't change as it is a resource.

// Sidenote: I completely forgot this was due until the email was sent through, and was busy with other assignments.
// this entire thing was written from ~3pm 15th to 5am on the 16th. Time management am I right.

/*
* Display the task banner informing the user of their available options.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void displayTasks() {
	std::cout << "[TASK] Please see a list of tasks detailed below. Enter a number, and the task will start.\n";
	std::cout << "[TASK] 1: Word search - Is a word in the dictionary?\n";
	std::cout << "[TASK] 2: Find words - Find all words containing a specified character n times.\n";
	std::cout << "[TASK] 3: List some words - List all words containing a \"q\" without a following \"u\".\n";
	std::cout << "[TASK] 4: Palindrome - Returns all words that are palindromes.\n";
	std::cout << "[TASK] 5: Anagrams - Returns all the words that are anagrams of a specified word.\n";
	std::cout << "[TASK] 6: Guessing Game - Presents the definition of a random noun, user has three tries to guess the noun.\n";
	std::cout << "[TASK] 7: Cheat at Wordle - User can specify the grey letters, yellow and green letters as displayed in Wordle. Program will recommend words to try.\n";
}

/*
* Main entry point of the program.
*
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 23/04/2022
*/
int main() {
	// Define the dictionary, and load the dictionary file as defined and mounted
	dict::ExtendedDictionary dict;
	dict.loadDictionary(DICTIONARY);

	while (true) {
		// Place a newline to space things out
		std::cout << "\n";
		displayTasks();
		// Prompt the user to enter a task
		std::string selectedTask = utils::getInput<std::string>("[TASK] Which task? ");

		// Switch statement, selects which task to perform and will prompt
		// if an invalid entry is received.
		switch (atoi(selectedTask.c_str())) {
		case 1:
			dict.taskOne();
			break;
		case 2:
			dict.taskTwo();
			break;
		case 3:
			dict.taskThree();
			break;
		case 4:
			dict.taskFour();
			break;
		case 5:
			dict.taskFive();
			break;
		case 6:
			dict.taskSix();
			break;
		case 7:
			dict.taskSeven();
			break;
		default:
			std::cout << "[TASK] Invalid task entered \"" << selectedTask << "\". Please try again.\n";
			break;
		}
	}

	system("pause");
	return 0;
}
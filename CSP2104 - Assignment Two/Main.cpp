#include "Utils.h"
#include "Word.h"
#include "Dictionary.h"

#include <iostream>

#define DICTIONARY "dictionary2022_S1.txt"

void displayTasks() {
	std::cout << "[TASK] Please see a list of tasks detailed below. Enter a number, and the task will start.\n";
	std::cout << "[TASK] 1: Word search - Is a word in the dictionary?\n";
	std::cout << "[TASK] 2: Find words - Find all words containing a specified character n times.\n";
	std::cout << "[TASK] 3: List some words - List all words containing a \"q\" without a following \"u\".\n";
}

int main() {
	dict::Dictionary dict;
	dict.loadDictionary(DICTIONARY);

	while (true) {
		std::cout << "\n";
		displayTasks();
		std::string selectedTask = utils::getInput<std::string>("[TASK] Which task? ");

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
		default:
			std::cout << "[TASK] Invalid task entered \"" << selectedTask << "\". Please try again.\n";
			break;
		}
	}

	system("pause");
	return 0;
}
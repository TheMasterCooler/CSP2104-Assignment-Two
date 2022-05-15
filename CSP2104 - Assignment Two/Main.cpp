#include "Utils.h"
#include "Word.h"
#include "Dictionary.h"

#include <iostream>

#define DICTIONARY "dictionary2022_S1.txt"

using namespace dict;

int main() {
	Dictionary dict;
	dict.loadDictionary(DICTIONARY);

	while (true) {
		// TODO: Task Banner
		std::string selectedTask = utils::getInput<std::string>("Which task? ");

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
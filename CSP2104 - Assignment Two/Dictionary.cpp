#include "Dictionary.h"

std::vector<word::Word>* dict::Dictionary::getList() {
	return &this->wordList;
}

void dict::Dictionary::pushWord(word::Word word) {
	this->wordList.push_back(word);
}

bool dict::Dictionary::loadDictionary(std::string filename) {
	std::cout << "[DICT] Loading dictionary.\n";
	std::string rawDict = utils::readFile(filename.c_str());
	std::cout << "[DICT] Processing dictionary.\n";
	std::vector<std::string> splitDict = utils::stringExplode(rawDict, "**\n");
	
	for (int i = 0; i < splitDict.size(); i++) {
		std::string section = splitDict.at(i);
		std::vector<std::string> wordData = utils::stringExplode(section, "\n");
		word::Word word = word::Word(wordData.at(1), wordData.at(0), wordData.at(2));

		this->pushWord(word);
	}
	std::vector<word::Word>* dictPointer = this->getList();

	std::cout << "[DICT] Done! Loaded " << dictPointer->size() << " words.\n";

	return true;
}

void dict::Dictionary::taskOne() {
	std::vector<word::Word>* dictionary = this->getList();

	std::string choice = utils::toLower(utils::getInput<std::string>("[T1] Please enter a word: "));
	
	bool found = false;
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word curWord = dictionary->at(i);

		found = (utils::toLower(curWord.getName()) == choice);
		if (found) {
			curWord.printDefinition();
			break;
		}
	}

	if (!found) std::cout << "[T1] Word not found.\n";
}

void dict::Dictionary::taskTwo() {
	std::cout << "[TASK] You chose task #2.\n";
	return;
}

void dict::Dictionary::taskThree() {
	std::cout << "[TASK] You chose task #3.\n";
	return;
}
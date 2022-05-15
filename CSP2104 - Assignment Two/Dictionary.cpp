#include "Dictionary.h"

std::vector<word::Word> dict::Dictionary::getList() {
	return this->wordList;
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
		word::Word word = word::Word(wordData.at(0), wordData.at(1), wordData.at(2));

		this->pushWord(word);
	}
	std::cout << "[DICT] Done! Loaded " << this->getList().size() << " words.\n";

	return true;
}

void dict::Dictionary::taskOne() {
	std::cout << "[TASK] You chose task #1.\n";
	return;
}

void dict::Dictionary::taskTwo() {
	std::cout << "[TASK] You chose task #2.\n";
	return;
}

void dict::Dictionary::taskThree() {
	std::cout << "[TASK] You chose task #3.\n";
	return;
}
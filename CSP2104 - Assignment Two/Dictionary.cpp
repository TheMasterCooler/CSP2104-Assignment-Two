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
		word::Word word = word::Word(utils::toLower(wordData.at(1)), wordData.at(0), wordData.at(2));

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
		word::Word* curWord = &dictionary->at(i);

		found = (curWord->getName() == choice);
		if (found) {
			curWord->printDefinition();
			break;
		}
	}

	if (!found) std::cout << "[ERROR] Word not found.\n";
}

void dict::Dictionary::taskTwo() {
	std::vector<word::Word>* dictionary = this->getList();

	// Using std::tolower not my function because that's designed to work on chars.
	// In fact my function is a wrapper for std::tolower :)
	char userChar = std::tolower(utils::getInput<char>("[T2] Please enter a character: "));
	int userOccur = utils::getInput<int>("[T2] Please enter a number of occurances: ");

	if (userOccur <= 0) {
		std::cout << "[ERROR] Please enter a positive number.\n";
		return;
	}

	std::vector<word::Word*> matchedWords;
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);
		int charCount = 0;

		for (int j = 0; j < curWord->getName().size(); j++) { if (userChar == curWord->getName().at(j)) { charCount++; } }
		if (charCount >= userOccur) matchedWords.push_back(curWord);
	}

	if (!matchedWords.empty()) {
		std::cout << "-----======= Word List =======-----\n";
		for (int i = 0; i < matchedWords.size(); i++) std::cout << matchedWords.at(i)->getName() << "\n";
		std::cout << "-----=========================-----\n";
		std::cout << "[T2] Your character appeared in " << matchedWords.size() << " different words!\n";
	} else {
		std::cout << "[ERROR] Your character did not appear in any words " << userOccur << " times or more.\n";
	}
}

void dict::Dictionary::taskThree() {
	std::vector<word::Word>* dictionary = this->getList();
	std::vector<word::Word*> matchedWords;

	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);

		bool lastQ = false;
		for (int j = 0; j < curWord->getName().size(); j++) {
			char curChar = curWord->getName().at(j);
			if ((curChar != *"u" && lastQ) || (curChar == *"q" && j + 1 == curWord->getName().size())) matchedWords.push_back(curWord);
			lastQ = (curChar == *"q");
		}
	}

	if (!matchedWords.empty()) {
		std::cout << "-----======= Word List =======-----\n";
		for (int i = 0; i < matchedWords.size(); i++) std::cout << matchedWords.at(i)->getName() << "\n";
		std::cout << "-----=========================-----\n";
	}
	else {
		std::cout << "[ERROR] No words were found. Something went wrong!\n";
	}
}

void dict::ExtendedDictionary::taskFour() {
	std::vector<word::Word>* dictionary = this->getList();
	std::vector<word::Word*> palindromes;

	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);
		int wordSize = curWord->getName().size();
		bool pdrome = true;
		for (int j = 0; j < wordSize; j++) {
			int opposite = wordSize - j - 1;
			pdrome = (pdrome && (curWord->getName().at(j) == curWord->getName().at(opposite)));
		}
		if (pdrome) palindromes.push_back(curWord);
	}

	if (!palindromes.empty()) {
		std::cout << "-----======= Word List =======-----\n";
		for (int i = 0; i < palindromes.size(); i++) std::cout << palindromes.at(i)->getName() << "\n";
		std::cout << "-----=========================-----\n";
		std::cout << "[T4] There are " << palindromes.size() << " words that are palindromes in the dictionary!\n";
	}
	else {
		std::cout << "[ERROR] No palindromes were found. Something went wrong!\n";
	}
}

void dict::ExtendedDictionary::taskFive() {
	return;
}

void dict::ExtendedDictionary::taskSix() {
	return;
}

void dict::ExtendedDictionary::taskSeven() {
	return;
}
#pragma once

#include <iostream>
#include <vector>

#include "Utils.h"
#include "Word.h"

#define ANAGRAM_LENGTH 256 // The length of the array used for anagrams. This is plenty as the highest ASCII code is 255.

namespace dict {
	class Dictionary {
	private:
		std::vector<word::Word> wordList;
	public:
		std::vector<word::Word>* getList(); // Retrieves the worldlist

		void pushWord(word::Word); // Pushes a word to the wordlist
		bool loadDictionary(std::string); // Returns boolean if the dictionary is loaded

		void taskOne();
		void taskTwo();
		void taskThree();
	};

	class ExtendedDictionary : public Dictionary {
	public:
		void taskFour();
		void taskFive();
		void taskSix();
		void taskSeven();
	};
}
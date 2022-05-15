#pragma once

#include <iostream>
#include <vector>

#include "Utils.h"
#include "Word.h"

namespace dict {
	class Dictionary {
	private:
		std::vector<word::Word> wordList;
	public:
		std::vector<word::Word> getList(); // Retrieves the worldlist

		void pushWord(word::Word); // Pushes a word to the wordlist
		bool loadDictionary(std::string); // Returns boolean if the dictionary is loaded

		void taskOne();
		void taskTwo();
		void taskThree();
	};
}
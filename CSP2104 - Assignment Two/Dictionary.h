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
		bool loadDictionary(std::string); // Returns boolean if the dictionary is loaded
	};
}
#pragma once

#include <iostream>
#include <unordered_map>
#include <stdlib.h>

#include "Utils.h"

namespace word {
	class Word {
	private:
		std::string name;
		std::string type;
		std::string definition;
		std::string prettyType;
		int length;
		bool fiveLetters;
	public:
		std::string getName();
		std::string getType();
		std::string getDefinition();
		std::string getPrettyType();
		int getLength();
		
		void printDefinition();

		bool wordleHasYellowLetters(std::vector<std::string>);
		bool wordleExcludesGreyLetters(std::vector<std::string>);
		bool wordleHasGreenLetters(std::vector<std::string>);
		bool wordleIsFiveLetters();

		Word(std::string, std::string, std::string);
	};

	std::string getWordIdentifier(std::string);
}
#include "Word.h"

/*
* Take a word type (n, v, adv, etc..) and convert that to a pretty representation.
*
* Param(s):
*	wordType (std::string) - The dirty word type (n, v, adv, etc..) to convert.
* Return:
*	std::string - A prettier string matching the word type.
* Author:
*	Ben Armstrong (10547876) - 22/02/2022
* Notes:
*	This is a really dirty solution. It's the best I could come up with at the
*	time due to the workings of switches and strings.
*/
std::string word::getWordIdentifier(std::string wordType) {
	// Create an unordered map containing std::strings as the key and value.
	std::unordered_map<std::string, std::string> types;

	// Align each identified (LEFT) to the correct cleaned up option (RIGHT)
	types["v"] = "(v.)";
	types["n"] = "(n.)";
	types["adv"] = "(adv.)";
	types["adj"] = "(adj.)";
	types["prep"] = "(prep.)";
	types["pn"] = "(pn.)";
	types["n_and_v"] = "(n.v.)";
	types["misc"] = "(misc.)";

	std::string ppValue = types[wordType];
	// Ternary statement if ppValue is null (didn't hit a valid identifier) return (NULL)
	return (ppValue == "") ? "(NULL)" : ppValue;
}

/*
* Outputs the definition of the word to the console, in the correct format.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void word::Word::printDefinition() {
	std::cout << "-----======= Word Info =======-----\n";
	std::cout << this->getName() << " | " << this->getPrettyType() << " | " << this->getDefinition() << "\n";
	std::cout << "-----=========================-----\n";
}

/*
* One of the functions for the Wordle minigame. This function will iterate over a string
* and return true if all of the supplied letters are present ANYWHERE within the string.
* 
* Param(s):
*	letters (std::vector<std::string>) - Vector of strings, these should be singular letters to search for.
* Return:
*	bool - Does the word contain all of the letters?
* Author:
*	Ben Armstrong (10547876) - 16/05/2022
*/
bool word::Word::wordleHasYellowLetters(std::vector<std::string> letters) {
	// Create a map array, used to verify at the end everything has beenf ound
	bool foundMap[WORD_MAP_LENGTH] = { false };

	// Iterate over the word name and compare each character
	for (int i = 0; i < this->getName().size(); i++) {
		char wordChar = this->getName().at(i);
		bool charCompliant = false;
		// For each character in the name, iterate over the supplied letters
		// check if there is a match. If so, register in the found table and continue
		for (int j = 0; j < letters.size(); j++) {
			char userChar = letters.at(j).at(0);
			if (wordChar == userChar) {
				foundMap[wordChar] = true;
				charCompliant = true;
				break;
			}
		}
	}

	// Review the foundMap array and confirm all letters are accounted for
	// if so, return true.
	bool overallCompliant = true;
	for (int i = 0; i < letters.size(); i++) {
		char userChar = letters.at(i).at(0);
		overallCompliant = overallCompliant && (foundMap[userChar]);
	}

	return overallCompliant;
}

/*
* Takes in a string of letters followed by numbers as characters and positions.
* Checks over the word and confirms all of the letters are at the user specified
* positions. This is used in the Wordle application.
* 
* Param(s):
*	std::vector<std::string> - Vector of characters and positions. E.G (a1, b2, c3, d4)
* Return:
*	bool - Are all the characters present at the specified locations
* Author:
*	Ben Armstrong (10547876) - 16/05/2022
*/
bool word::Word::wordleHasGreenLetters(std::vector<std::string> letters) {
	// Create two maps. One will store the positions (ASCII codes of integers) and the other
	// will store if all the characters are accounted for.
	bool foundMap[WORD_MAP_LENGTH] = { false };
	int posMap[WORD_MAP_LENGTH] = { 0 };

	// Iterate over the letters provided by the user
	for (int i = 0; i < letters.size(); i++) {
		// Are there less than two? If so break out as this is going to error.
		if (letters.at(i).size() < 2) return false;

		// Load the character and position into the position map. Subtract 1
		// due to the offset due to the user not agreeing that arrays start at 0.
		// ((except Lua))
		char userChar = letters.at(i).at(0);
		int userPos = letters.at(i).at(1);
		posMap[userPos - 1] = userChar;
	}

	// Iterate over the name of the word
	for (int i = 0; i < this->getName().size(); i++) {
		char curChar = this->getName().at(i);
		// Is this position in the posMap documented, if so, is it the right char?
		// if it is, load into the foundMap for validation
		// posMap i + 48 as this is using ASCII and 0 in ASCII is 48.
		if (posMap[i + 48] == curChar) foundMap[curChar] = true;
	}

	// Iterate over the foundMap and confirm that all letters are accounted for
	// if so, return true.
	bool overallCompliant = true;
	for (int i = 0; i < letters.size(); i++) {
		char userChar = letters.at(i).at(0);
		overallCompliant = overallCompliant && (foundMap[userChar]);
	}
	return overallCompliant;
}

/*
* Wordle function, will iterate through the word and confirm none of the user-specified
* characters are present in the word.
* 
* Param(s):
*	std::vector<std::string> - Vector of strings, all the letters that should NOT appear
* Return:
*	bool - Did the word comply? Were all the characters unaccounted for?
*/
bool word::Word::wordleExcludesGreyLetters(std::vector<std::string> letters) {
	// Create two maps to compare later
	bool greyMap[WORD_MAP_LENGTH] = { false };
	bool selfMap[WORD_MAP_LENGTH] = { false };

	// Iterate over both the users' letters, and the word to assemble the maps
	for (int i = 0; i < letters.size(); i++) greyMap[letters.at(i).at(0)] = true;
	for (int i = 0; i < this->getName().size(); i++) selfMap[this->getName().at(i)] = true;

	bool compliant = true;
	// Iterate over the full length of the maps
	for (int i = 0; i < WORD_MAP_LENGTH; i++) {
		// If both maps are true, a character was found and therefore we have failed
		if (greyMap[i] && selfMap[i]) {
			compliant = false;
		}
	}

	return compliant;
}

/*
* Miscellaneous getters. These all just retrieve a variable directly from the private
* section of the class. I hope these don't need their own explanations
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
std::string word::Word::getName() { return this->name; }
std::string word::Word::getType() { return this->type; }
std::string word::Word::getDefinition() { return this->definition; }
std::string word::Word::getPrettyType() { return this->prettyType; }
int word::Word::getLength() { return this->length; }
bool word::Word::wordleIsFiveLetters() { return this->fiveLetters; }

/*
* Word constructor, used to setup each Word object when being loaded, this is used
* to automatically setup all info we will need. Such as pretty type etc.
*
* Param(s):
*	wordName (std::string) - The name of the word.
*	wordType (std::string) - The short type of the word.
*	wordDefinition (std::string) - The definition of the word
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
word::Word::Word(std::string wordName, std::string wordType, std::string wordDefinition) {
	this->name = wordName;
	this->type = wordType;
	this->definition = wordDefinition;
	this->prettyType = getWordIdentifier(wordType);
	this->length = wordName.size();
	this->fiveLetters = (this->length == 5);
}
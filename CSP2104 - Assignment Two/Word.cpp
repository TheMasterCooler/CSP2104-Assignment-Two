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

word::Word::Word(std::string wordName, std::string wordType, std::string wordDefinition) {
	// Maybe error check just in case?
	this->name = wordName;
	this->type = wordType;
	this->definition = wordDefinition;
	this->prettyType = getWordIdentifier(wordType);
}

void word::Word::printDefinition() {
	std::cout << "egg\n";
}

std::string word::Word::getName() { return this->name; }
std::string word::Word::getType() { return this->type; }
std::string word::Word::getDefinition() { return this->definition; }
std::string word::Word::getPrettyType() { return this->prettyType; }
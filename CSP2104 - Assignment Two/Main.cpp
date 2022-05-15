#include "Word.h"
#include "Dictionary.h"
#include "Utils.h"

#include <iostream>

#define DICTIONARY "dictionary2022_S1.txt"

using namespace dict;

void main() {
	utils::print("hello");
	Dictionary dict;
	dict.loadDictionary(DICTIONARY);

	system("pause");
	return;
}
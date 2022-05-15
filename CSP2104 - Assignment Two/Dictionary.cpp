#include "Dictionary.h"

/*
* Retreive the pointer to the WordList containing all the Word objects.
* 
* Param(s):
*	N/A
* Return:
*	std::vector<word::Word>* - Pointer to the wordlist
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
std::vector<word::Word>* dict::Dictionary::getList() {
	return &this->wordList;
}

/*
* Pushes a word back into the WordList. Only used in construction,
* effectively a setter.
* 
* Param(s):
*	word (word::Word) - Completed word object to be pushed
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void dict::Dictionary::pushWord(word::Word word) {
	this->wordList.push_back(word);
}


/*
* Read the dictionary file, process it, convert all the data into
* usable Word objects, and push into the parent WordList.
* 
* Param(s):
*	filename (std::string) - The path to the dictionary file to be loaded
* Return(s):
*	bool - Dictionary loaded successfully
*/
bool dict::Dictionary::loadDictionary(std::string filename) {
	// Read the dictionary file
	std::cout << "[DICT] Loading dictionary.\n";
	std::string rawDict = utils::readFile(filename.c_str());
	// Split the dictionary by the delimeter character
	std::cout << "[DICT] Processing dictionary.\n";
	std::vector<std::string> splitDict = utils::stringExplode(rawDict, "**\n");
	
	// Iterate over the dictionary, break down each section into word objects
	for (int i = 0; i < splitDict.size(); i++) {
		std::string section = splitDict.at(i);
		std::vector<std::string> wordData = utils::stringExplode(section, "\n");
		word::Word word = word::Word(utils::toLower(wordData.at(1)), wordData.at(0), wordData.at(2));

		// Push the assembled word object into the stack
		this->pushWord(word);
	}
	// User feedback
	std::vector<word::Word>* dictPointer = this->getList();

	std::cout << "[DICT] Done! Loaded " << dictPointer->size() << " words.\n";

	return true;
}

/*
* Prompt a user to input a word. If the word is found in the dictionary, output the
* definition, type of word and word itself in a pretty format.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void dict::Dictionary::taskOne() {
	std::vector<word::Word>* dictionary = this->getList();

	std::string choice = utils::toLower(utils::getInput<std::string>("[T1] Please enter a word: "));
	
	// Iterate over the dictionary, if the word is a match,
	// print the definition using the helper function and end.
	bool found = false;
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);

		found = (curWord->getName() == choice);
		if (found) {
			curWord->printDefinition();
			break;
		}
	}

	// If the word was not found, inform the user.
	if (!found) std::cout << "[ERROR] Word not found.\n";
}

/*
* Prompt a user for a character and a specified number of occurances,
* search through the dictionary and output a list of words matching the critera.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void dict::Dictionary::taskTwo() {
	std::vector<word::Word>* dictionary = this->getList();

	// Using std::tolower not my function because that's designed to work on chars.
	// In fact my function is a wrapper for std::tolower :)
	char userChar = std::tolower(utils::getInput<char>("[T2] Please enter a character: "));
	int userOccur = utils::getInput<int>("[T2] Please enter a number of occurances: ");

	// If the user enters a negative number, run again.
	if (userOccur <= 0) {
		std::cout << "[ERROR] Please enter a positive number.\n";
		return;
	}

	// Iterate over the dictionary, identify all words that match.
	std::vector<word::Word*> matchedWords;
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);
		int charCount = 0;

		// Iterate through the current word, if the character is present, increment the integer by 1.
		for (int j = 0; j < curWord->getName().size(); j++) { if (userChar == curWord->getName().at(j)) { charCount++; } }
		// If charCount is higher than the threshhold, push back to the vector and continue.
		if (charCount >= userOccur) matchedWords.push_back(curWord);
	}

	// If words were found, output to the screen in a nice format,
	// if not, inform the user and end.
	if (!matchedWords.empty()) {
		std::cout << "-----======= Word List =======-----\n";
		for (int i = 0; i < matchedWords.size(); i++) std::cout << matchedWords.at(i)->getName() << "\n";
		std::cout << "-----=========================-----\n";
		std::cout << "[T2] Your character appeared in " << matchedWords.size() << " different words!\n";
	} else {
		std::cout << "[ERROR] Your character did not appear in any words " << userOccur << " times or more.\n";
	}
}

/*
* Return all the words present in the dictionary, containing the letter Q
* without a letter U following.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void dict::Dictionary::taskThree() {
	std::vector<word::Word>* dictionary = this->getList();
	std::vector<word::Word*> matchedWords;

	// Iterate over the dictionary and retrieve every single word
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);

		// Set a boolean to be used as memory if a Q was recently hit
		bool lastQ = false;
		for (int j = 0; j < curWord->getName().size(); j++) {
			char curChar = curWord->getName().at(j);
			// IF the current character is NOT a U and there was a Q previously.
			// OR the current character is a Q and the next character is the end of string
			// PUSH BACK
			if ((curChar != *"u" && lastQ) || (curChar == *"q" && j + 1 == curWord->getName().size())) matchedWords.push_back(curWord);
			// If the current character is a Q, set the variable for the next round
			lastQ = (curChar == *"q");
		}
	}

	// Output the information to the user
	if (!matchedWords.empty()) {
		std::cout << "-----======= Word List =======-----\n";
		for (int i = 0; i < matchedWords.size(); i++) std::cout << matchedWords.at(i)->getName() << "\n";
		std::cout << "-----=========================-----\n";
	} else {
		std::cout << "[ERROR] No words were found. Something went wrong!\n";
	}
}

/*
* Iterate through the dictionary, and display a list of palindromes
* words which are spelt the same backwards as they are forwards.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void dict::ExtendedDictionary::taskFour() {
	std::vector<word::Word>* dictionary = this->getList();
	std::vector<word::Word*> palindromes;

	// Iterate over the dictionary
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);
		int wordSize = curWord->getName().size();

		// Initiate a variable, this will be reset if the word is NOT a palindrome
		bool pdrome = true;
		// Iterate over the characters within the word stopping half way as there is no need to continue
		// Halfway is calculated by dividing wordSize as a double and ceiling
		// This ensures it will round up. E.G: wordSize = 3 | wordSize / 2.0f = 1.5f will round up to 2.0f (2)
		for (int j = 0; j < (ceil((double)wordSize / 2.0f)); j++) {
			// Get the opposite of J, the last character initially
			int opposite = wordSize - j - 1;
			// IF the word has so far been equal
			// AND the current character is the same as the opposite character
			// Continue to set pdrome and proceed
			pdrome = (pdrome && (curWord->getName().at(j) == curWord->getName().at(opposite)));
		}
		if (pdrome) palindromes.push_back(curWord);
	}

	// Output the findings to the user
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

/*
* Prompts the user for a word, iterates through the dictionary and
* returns all the anagrams of that word. E.G, admirer, married, god, dog
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void dict::ExtendedDictionary::taskFive() {
	std::string userWord = utils::toLower(utils::getInput<std::string>("[T5] Please enter a word: "));

	std::vector<word::Word>* dictionary = this->getList();
	std::vector<word::Word*> anagrams;

	// Establish a map array, 256 characters long to account for all ASCII characters
	// and count occurances of characters in the user provided word
	int userCount[WORD_MAP_LENGTH] = { 0 };
	for (int i = 0; i < userWord.size(); i++) userCount[userWord.at(i)]++;

	// Iterate over the dictionary 
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);
		// IF the word is not the same as the user specified word, and is the same size
		if ((curWord->getLength() == userWord.size()) && (curWord->getName() != userWord)) {
			bool anagram = true;

			// Define the same character mesh, iterate over the word and increment that
			int curCount[WORD_MAP_LENGTH] = { 0 };
			for (int j = 0; j < curWord->getLength(); j++) curCount[curWord->getName().at(j)]++;
			// Finally, compare the two meshes and confirm if they are identical
			// if they are, we have an anagram
			for (int j = 0; j < WORD_MAP_LENGTH; j++) {
				anagram = (anagram && (userCount[j] == curCount[j]));
			}

			if (anagram) {
				anagrams.push_back(curWord);
			}
		}
	}

	// Display to the user
	if (!anagrams.empty()) {
		std::cout << "-----======= Word List =======-----\n";
		for (int i = 0; i < anagrams.size(); i++) std::cout << anagrams.at(i)->getName() << "\n";
		std::cout << "-----=========================-----\n";
		std::cout << "[T5] There are " << anagrams.size() << " anagrams of that word in the dictionary.\n";
	}
	else {
		std::cout << "[ERROR] No anagrams were found.\n";
	}

	return;
}

/*
* Guessing game. This function is to present the user with the definition of a random noun
* alongside it's length. The user will have three attempts to guess the noun, after the
* first incorrect guess, the first letter is revealed. The second guess, the second later
* and finally the third guess, if incorrect will provide the user the entire word.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
*/
void dict::ExtendedDictionary::taskSix() {
	// Seed that random number generator using time
	// without this the same is generated every compile
	srand(time(NULL));

	std::vector<word::Word>* dictionary = this->getList();
	
	// Get all nouns and push them into a vector of pointers
	std::vector<word::Word*> nouns;
	
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);
		if (curWord->getType() == "n") nouns.push_back(curWord);
	}

	// Randomly generate a number between 0 and the amount of nouns
	// select a random noun.
	int randomIndex = rand() % nouns.size();
	word::Word* randomWord = nouns.at(randomIndex);

	// Provide the user with the information about the noun
	std::cout << "[T6] Please see below for a definition of a random noun.\n";
	std::cout << randomWord->getDefinition() << "\n";
	std::cout << "[T6] The noun is " << randomWord->getLength() << " characters long.\n";
	
	// Initialise guessCount and start the main game loop
	int guessCount = 0;

	while (guessCount < 3) {
		std::string guess = utils::getInput<std::string>("[T6] Please enter a guess: ");
		guessCount++;

		// If the user guesses correctly, congratulate and finish
		if (guess == randomWord->getName()) {
			std::cout << "[T6] Congratulations! You guessed the word correctly.\n";
			break;
		} else {
			// Dependant on the guess, print a different message
			switch (guessCount) {
			case 1:
				std::cout << "[T6] Incorrect. The first character is: \"" << randomWord->getName().at(0) << "\". Please try again.\n";
				break;
			case 2:
				std::cout << "[T6] Incorrect. The first two characters are: \"" << randomWord->getName().substr(0, 2) << "\". You have one final try.\n";
				break;
			case 3:
				std::cout << "[T6] Incorrect. The word was \"" << randomWord->getName() << "\". Better luck next time!\n";
				break;
			default:
				std::cout << "[T6] Something went wrong. Please try again.\n";
				break;
			}
		}
	}
}

/*
* Cheat at Wordle. This function is designed to take three sets of user input and will
* recommend a list of words to try for Wordle. The user can specify A) Grey letters, letters
* which do NOT appear in the word. B) Yellow Letters, letters which DO appear in the word in any
* location. and C) Green Letters, letters that DO appear in the word in a specified location.
* 
* Syntax is as follows, to be supplied using "/" as a delimter. E.G, a/b/c/d or for GREEN a1/b2/c3/d4
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 16/05/2022
*/
void dict::ExtendedDictionary::taskSeven() {
	std::cout << "\n";
	std::cout << "[T7] Welcome to Cheat at Wordle! This application is designed to suggest words to use during the Wordle.\n";
	std::cout << "[T7] Wordle is a word-based guessing game, you are presented with a 5x6 square and are challenged to guess five letter words.\n";
	std::cout << "[T7] To aide, you are provided hints as you go along. If you enter a character that is NOT present in the correct word, that character will show up as GREY.\n";
	std::cout << "[T7] If you enter a character that IS present in the correct word, just in the incorrect position, the character will show up as YELLOW.\n";
	std::cout << "[T7] If you enter a character in the CORRECT location, it will show up as green. You have six attempts to guess the word correctly.\n";
	std::cout << "[T7] To use this application, enter your characters separated by the \"/\" character and with a trailing \"/\" at the end. See below for an example grey and green letter input.\n";
	std::cout << "[T7] Grey: a/b/c/d/\n";
	std::cout << "[T7] Green: a1/b2/c3/d4/\n";
	std::cout << "[T7] The green letters are different, as you need to specify an integer for a location as well.\n";
	std::cout << "[T7] Good luck!\n";

	// Retrieve the letters from the user. These need to be processed with the stringExplode function
	std::string rawGrey = utils::toLower(utils::getInput<std::string>("[T7] Please enter a list of letters to exclude (Grey Letters): ")); // a b c d
	std::vector<std::string> greyLetters = utils::stringExplode(rawGrey, "/");
	std::string rawYellow = utils::toLower(utils::getInput<std::string>("[T7] Please enter a list of letters to include anywhere (Yellow/Orange Letters): ")); // a b c d
	std::vector<std::string> yellowLetters = utils::stringExplode(rawYellow, "/");
	std::string rawGreen = utils::toLower(utils::getInput<std::string>("[T7] Please specify a list of letters to include alongside their positions (Green Letters): ")); // a1 b2 c3 d4
	std::vector<std::string> greenLetters = utils::stringExplode(rawGreen, "/");

	std::vector<word::Word>* dictionary = this->getList();
	std::vector<word::Word*> probableAnswers;

	// Iterate over the dictionary
	for (int i = 0; i < dictionary->size(); i++) {
		word::Word* curWord = &dictionary->at(i);

		// Perform each of the qualification steps and if they all succeed, push into a vector for display to the user
		if (curWord->wordleIsFiveLetters()) {
			if (curWord->wordleExcludesGreyLetters(greyLetters)) {
				if (curWord->wordleHasYellowLetters(yellowLetters)) {
					if (curWord->wordleHasGreenLetters(greenLetters)) {
						probableAnswers.push_back(curWord);
					}
				}
			};
		}
	}

	// Display the results to the user
	if (!probableAnswers.empty()) {
		std::cout << "-----======= Word List =======-----\n";
		for (int i = 0; i < probableAnswers.size(); i++) std::cout << probableAnswers.at(i)->getName() << "\n";
		std::cout << "-----=========================-----\n";
		std::cout << "[T7] Identified " << probableAnswers.size() << " possible answers.\n";
	}
	else {
		std::cout << "[ERROR] No answers were found.\n";
	}
}
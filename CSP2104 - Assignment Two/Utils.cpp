#include "Utils.h"

/*
* Takes a string and splits it into chunks based on a delimeter.
*
* Param(s):
*	content (std::string) - The string that should be split.
*	delimeter (std::string) - The delimeter to split the string by.
* Return:
*	std::vector<std::string> - A vector containing all the chunks of a string.
* Author:
*	Ben Armstrong (10547876) - 21/02/2022
*/
std::vector<std::string> utils::stringExplode(std::string content, std::string delimeter) {
	std::vector<std::string> retVector;

	size_t cursor = 0;
	size_t delimPos = 0;
	size_t delimLength = delimeter.length();
	// Iterate over the string, find the location of each delimeter relative to the previous point.
	while ((delimPos = content.find(delimeter, cursor)) != std::string::npos) {
		// Substr, extract that section of text.
		retVector.push_back(content.substr(cursor, (delimPos - cursor)));
		// Update the current cursor to prevent a buffer overflow (this took too long to figure out)
		cursor = delimPos + delimLength;
	}

	return retVector;
}

/*
* Reads a file at a specified path, and returns the contents in a string.
*
* Param(s):
*	filePath (const char*) - The path to the file that will be read.
* Return:
*	std::string - A string of the file's contents.
* Author:
*	Ben Armstrong (10547876) - 21/02/2022
*/
std::string utils::readFile(const char* filePath) {
	// Open a file stream to read the file.
	std::ifstream fStream(filePath);
	std::string fStr;

	if (fStream) {
		// If file is found, read the buffer and load into a buffer object. Convert to string.
		std::ostringstream sbuf;
		sbuf << fStream.rdbuf();
		fStr = sbuf.str();
	}

	// Close off the file handle to be clean.
	fStream.close();

	return fStr;
}

/*
* Provides a safe method of retrieving input from the user. Protects against
* overflows and bad bits.
*
* Param(s):
*	prompt (std::string) - The prompt to display before the data entry.
* Return:
*	input - Automatically assigning type, value entered by user.
* Author:
*	Ben Armstrong (10547876) - 14/03/2022
* Notes:
*	This is pretty nice. I tried to make it work with pointers, however had
*	multiple issues. 100% my fault. Please see link below for "inspiration"
*	https://stackoverflow.com/questions/13212043/loop-until-integer-input-is-in-required-range-fails-to-work-with-non-digit-chara
*/
// Create a template, this will auto adapt to the type entered at function execution
template<class input>
input utils::getInput(std::string prompt) {
	input userInput;

	// Prompt the user and define a holding variable
	std::cout << prompt;
	std::string line;
	// Indefinitely read user input until something valid is entered
	while (std::getline(std::cin, line)) {
		std::stringstream linestream(line);
		// Is it the right type, if incorrect prompt user and retry
		if (!(linestream >> userInput)) {
			std::cout << "Invalid input entered. Please try again.\n";
			std::cout << prompt;
			continue;
		}
		break;
	}
	return userInput;
}

/*
* Simply a debug function, this fixes a linker issue with the getInput function.
* 
* Param(s):
*	N/A
* Return:
*	N/A
* Author:
*	Ben Armstrong (10547876) - 15/05/2022
* Notes:
*	Encountered an external dependancy linker issue with the utils::getInput function
*	after some research, determined this was due to the separate definitions of template
*	in the .cpp and .h file. This casued the compiler to wig out and error. Please see
*	below for details.
*	https://www.codeproject.com/Articles/48575/How-to-Define-a-Template-Class-in-a-h-File-and-Imp#:~:text=Getalue()%0A%7B%0A%20%20%20%20return%20m_Obj%3B%0A%7D-,Linking%20Issue,-With%20the%20above
*/
void test() { std::string test = utils::getInput<std::string>("test\n"); }

/*
* Converts a returned string entirely to lowercase.
*
* Param(s):
*	toTransform (std::string) - String to be converted to lower case
* Return:
*	std::string - Lowercase converted string
* Author:
*	Ben Armstrong (10547876) - 22/03/2022
* Notes:
*	Researched how to resolve this issue and came across the solution on StackOverflow.
*	https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
*/
std::string utils::toLower(std::string toTransform) {
	// Begin a transform to run a function over the entire entered string
	std::transform(toTransform.begin(), toTransform.end(), toTransform.begin(),
		[](unsigned char c) { return std::tolower(c); });
	// Transforms the string and converts each char to lowercase
	return toTransform;
}
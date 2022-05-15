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
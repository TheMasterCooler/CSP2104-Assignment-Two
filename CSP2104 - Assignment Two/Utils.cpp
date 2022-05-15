#include "Utils.h"

void utils::print(std::string message) {
	std::cout << message << std::endl;
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
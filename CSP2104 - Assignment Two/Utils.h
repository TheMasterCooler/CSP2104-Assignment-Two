#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

namespace utils {
	void print(std::string message); 

	std::string readFile(const char* filePath);
}
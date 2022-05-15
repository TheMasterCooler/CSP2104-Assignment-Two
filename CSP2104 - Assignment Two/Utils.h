#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

namespace utils {

	std::vector<std::string> stringExplode(std::string content, std::string delimeter);
	std::string readFile(const char* filePath);
	template<class input>
	input getInput(std::string);
	std::string toLower(std::string);
}
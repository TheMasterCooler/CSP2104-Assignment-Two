#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace utils {
	std::vector<std::string> stringExplode(std::string content, std::string delimeter);
	std::string readFile(const char* filePath);
}
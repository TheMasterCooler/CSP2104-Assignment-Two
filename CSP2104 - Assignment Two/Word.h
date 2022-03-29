#include <iostream>
#include <unordered_map>

namespace word {
	class Word {
	private:
		std::string name;
		std::string type;
		std::string definition;
		std::string prettyType; // Set this automatically in the constructor
		// Also wants a printDefinition function to output the definition as per task 1 in last assignment
		// TODO: Setters and getters
	public:
		// Don't need any setters seeing as everything can be done in constructor
		std::string getName();
		std::string getType();
		std::string getDefinition();
		std::string getPrettyType();
		
		void printDefinition();

		Word(std::string, std::string, std::string);
	};

	std::string getWordIdentifier(std::string);
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tokenizer.h"
#include "parser.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage is ./law <file-path>" << std::endl;
		return -1;
	}
	if (std::string(argv[1]) == "-help") {
		std::cout << "Usage is ./law <file-path>" << std::endl;
	}
	std::ifstream file(argv[1]);
	std::vector<std::string> lines;
	std::string lineText;

	while (std::getline(file, lineText)) {
		lines.push_back(lineText);
	}

	file.close();

	Tokenizer tokenizer(lines);
	try {
		tokenizer.tokenize();
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
		return -1;
	}
	Parser parser(tokenizer.getTokens());
	try {
		parser.parse();
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
		return -1;
	}


	return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tokenizer.h"
#include "parser.h"

void parseLines(std::vector<std::string>& lines);

void parseInput() {
	std::vector<std::string> lines;
	std::string lineText;

	while (1) {
		std::getline(std::cin, lineText);
		if (lineText == "") break;
		lines.push_back(lineText);
	}

	parseLines(lines);
}

void fileParse(char* filePath) {
	std::ifstream file(filePath);
	std::vector<std::string> lines;
	std::string lineText;

	while (std::getline(file, lineText)) {
		lines.push_back(lineText);
	}

	file.close();

	parseLines(lines);
}

void parseLines(std::vector<std::string>& lines) {
	Tokenizer tokenizer(lines);
	try {
		tokenizer.tokenize();
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
		return;
	}
	Parser parser(tokenizer.getTokens());
	try {
		parser.parse();
	}
	catch (std::runtime_error e) {
		std::cout << e.what() << std::endl;
		return;
	}
}

void whileInputParse() {
	std::vector<std::string> lines;
	std::string line;
	int lineCount = 0;
	Tokenizer tok(lines);
	Parser par;

	std::cout << "[" << lineCount << "] ";
	while (std::getline(std::cin, line)) {
		if (line == "exit") {
			break;
		} if (line == "clear") {
			system("clear");
			std::cout << "[" << lineCount << "] ";
			continue;
		}
		lines.clear();
		if ((int)std::count(line.begin(), line.end(), '{') > 0 && (int)std::count(line.begin(), line.end(), '}') == 0) {
			int openBrakAmount = (int)std::count(line.begin(), line.end(), '{');
			lines.push_back(line);
			while (openBrakAmount != 0) {
				std::cout << "... ";
				std::getline(std::cin, line);
				lines.push_back(line);
				openBrakAmount += (int)std::count(line.begin(), line.end(), '{');
				openBrakAmount -= (int)std::count(line.begin(), line.end(), '}');
			}
		}
		else {
			lines.push_back(line);
		}
		
		tok.updateLines(lines);
		tok.clearTokens();
		try {
			tok.tokenize();
		}
		catch (std::runtime_error e) {
			std::cout << e.what() << std::endl;
		}
		try {
			par.updateTokens(tok.getTokens());
			par.parse();
		}
		catch (std::runtime_error e) {
			std::cout << e.what() << std::endl;
		}

		lineCount++;
		std::cout << "[" << lineCount << "] ";
	}
}

int main(int argc, char** argv) {
	if (argc == 2) {
		if (std::string(argv[1]) == "-h") {
			std::cout << "Usage is ./law <file-path> or ./law" << std::endl;
			return 0;
		} 
		else if (std::string(argv[1]) == "-i") {
			parseInput();
			return 0;
		}
		fileParse(argv[1]);
	}
	else if (argc == 1) {
		whileInputParse();
	}
	else {
		std::cout << "Usage is ./law <file-path> or ./law" << std::endl;
	}


	return 0;
}

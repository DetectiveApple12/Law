#pragma once
#include "tokenizer.h"
#include <unordered_map>
#include <string>

class Parser
{
public:
	Parser(std::vector<std::vector<Token>> tokens);
	~Parser();
	void Parse();

private:
	unsigned int _currLine;
	unsigned int _curr;
	std::vector<std::vector<Token>> _tokens;
	std::unordered_map<std::string, std::string> _vars;
	int runCodeBrak = 0;
	int stopCodeBrak = 0;

	Token peek();
	Token getAndMove();
	bool operation(std::string a, std::string b, TokenType op);
	void checkSemi();

};

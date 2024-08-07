#pragma once
#include "tokenizer.h"
#include <unordered_map>
#include <string>

class Parser
{
public:
	Parser(std::vector<std::vector<Token>> tokens);
	~Parser();
	/*
	Function will parse the tokens and execute their functionality.
	*/
	void parse();

private:
	unsigned int _currLine;
	unsigned int _curr;
	std::vector<std::vector<Token>> _tokens;
	std::unordered_map<std::string, std::string> _vars;
	int runCodeBrak = 0;
	int stopCodeBrak = 0;

	/*
	Function will return the current token in the current line.
	*/
	Token peek();
	/*
	Function will return the next token in the current line.
	*/
	Token peekTwo();
	/*
	Function will return the current token in the current line and move to the next token.
	*/
	Token getAndMove();
	/*
	Function will make an operation such as ==, !=, < and > on two strings.
	*/
	bool operation(std::string a, std::string b, TokenType op);
	/*
	Function will check that the next token is a semi.
	*/
	void checkSemi();

};

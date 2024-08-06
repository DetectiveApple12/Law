#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

enum class TokenType {
	set, eq, rule, _if, open_brak, close_brak, open_par, close_par, out, str_lit, assign, semi, var_name, eol, neq, int_lit, larger, smaller, minus, in
};

struct Token {
	TokenType tokenType;
	std::string value;
};

class Tokenizer
{
public:
	Tokenizer(std::vector<std::string> text);
	~Tokenizer();
	/*
	Function will turn lines recieved from constructor to vector<vector<Token>>.
	*/
	void tokenize();
	std::vector<std::vector<Token>>& getTokens();

private:
	unsigned int _currLine;
	unsigned int _curr;
	std::vector<std::vector<Token>> _tokensSets;
	std::vector<Token> _tokens;
	std::vector<std::string> _lines;

	/*
	Function will return the current char in the current line.
	*/
	char peek();
	/*
	Function will return the current char in the current line and move to the next char.
	*/
	char getAndMove();
	/*
	Function will parse a var_name. 
	*/
	std::string parseVar();
	/*
	Function will parse a integer. 
	*/
	std::string parseDig();
	/*
	Function will parse a string literal.
	*/
	std::string parseStrLit();

};

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

enum class TokenType {
	set, eq, rule, _if, open_brak, close_brak, open_par, close_par, out, str_lit, assign, semi, var_name, eol, neq, int_lit, larger, smaller, minus
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
	void tokenize();
	std::vector<std::vector<Token>>& getTokens();

private:
	unsigned int _currLine;
	unsigned int _curr;
	std::vector<std::vector<Token>> _tokensSets;
	std::vector<Token> _tokens;
	std::vector<std::string> _lines;

	char peek();
	char getAndMove();
	std::string parseVar();
	std::string parseDig();
	std::string parseStrLit();

};

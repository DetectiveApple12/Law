#include "tokenizer.h"

Tokenizer::Tokenizer(std::vector<std::string> lines) 
	: _lines(lines), _curr(0), _tokens(), _currLine(0)
{
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::tokenize()
{
	if (this->_currLine == this->_lines.size()) return;

	this->_tokens.clear();

	std::string& currentLine = this->_lines[this->_currLine];
	while (this->_curr != currentLine.size()) {
		if (std::isalpha(peek())) {
			std::string value = parseVar();
			if (value == "out") {
				this->_tokens.push_back({ TokenType::out, value });
			}
			else if (value == "set") {
				this->_tokens.push_back({ TokenType::set, "" });
			}
			else if (value == "rule") {
				this->_tokens.push_back({ TokenType::rule, "" });
			}
			else if (value == "if") {
				this->_tokens.push_back({ TokenType::_if, "" });
			}
			else {
				this->_tokens.push_back({ TokenType::var_name, value });
			}
		}
		else if (std::isdigit(peek())) {
			std::string value = parseDig();
			this->_tokens.push_back({ TokenType::int_lit, std::to_string(stoi(value)) });
		}
		else if (peek() == '\"') {
			std::string value = parseStrLit();
			this->_tokens.push_back({ TokenType::str_lit, value });
		}
		else if (peek() == ';') {
			getAndMove();
			this->_tokens.push_back({ TokenType::semi, "" });
		}
		else if (peek() == ' ' || peek() == '\t') {
			getAndMove();
		}
		else if (peek() == '=') {
			getAndMove();
			if (peek() == '=') {
				getAndMove();
				this->_tokens.push_back({ TokenType::eq, "" });
			}
			else {
				this->_tokens.push_back({ TokenType::assign, "" });
			}
		}
		else if (peek() == '!') {
			getAndMove();
			if (peek() == '=') {
				getAndMove();
				this->_tokens.push_back({ TokenType::neq, "" });
			}
		}
		else if (peek() == '>') {
			getAndMove();
			this->_tokens.push_back({ TokenType::larger, "" });
		}
		else if (peek() == '<') {
			getAndMove();
			this->_tokens.push_back({ TokenType::smaller, "" });
		}
		else if (peek() == '{') {
			getAndMove();
			this->_tokens.push_back({ TokenType::open_brak, "" });
		}
		else if (peek() == '}') {
			getAndMove();
			this->_tokens.push_back({ TokenType::close_brak, "" });
		}
		else if (peek() == '(') {
			getAndMove();
			this->_tokens.push_back({ TokenType::open_par, "" });
		}
		else if (peek() == ')') {
			getAndMove();
			this->_tokens.push_back({ TokenType::close_par, "" });
		}
		else if (peek() == '-') {
			getAndMove();
			if (peek() == '-') {
				break;
			}
			else {
				this->_tokens.push_back({ TokenType::minus, "" });
			}
		}
		else {
			std::string error = "TokenizeError: Unrecognized Token `" + std::string(1, peek()) + "` [Line " + std::to_string(this->_currLine + 1) + "]";
			throw std::runtime_error(error);
		}
	}

	this->_tokensSets.push_back(this->_tokens);
	this->_curr = 0;
	this->_currLine++;
	tokenize();
}

std::vector<std::vector<Token>>& Tokenizer::getTokens()
{
	return this->_tokensSets;
}

char Tokenizer::peek()
{
	if (this->_curr >= this->_lines[this->_currLine].size()) {
		return '\0';
	}
	return this->_lines[this->_currLine][this->_curr];
}

char Tokenizer::getAndMove()
{
	if (this->_curr >= this->_lines[this->_currLine].size()) {
		return '\0';
	}
	this->_curr++;
	return this->_lines[this->_currLine][this->_curr - 1];
}

std::string Tokenizer::parseVar()
{
	std::string value = "";
	while (std::isalnum(peek())) {
		value += getAndMove();
	}
	return value;
}

std::string Tokenizer::parseDig()
{
	std::string value = "";
	while (std::isdigit(peek())) {
		value += getAndMove();
	}
	return value;
}

std::string Tokenizer::parseStrLit()
{
	std::string value = "";
	getAndMove();
	while (peek() != '\"') {
		if (peek() == '\"') break;
		value += getAndMove();
	}
	getAndMove();
	return value;
}

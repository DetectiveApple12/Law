#include "tokenizer.h"

Tokenizer::Tokenizer(std::vector<std::string> lines) 
	: _lines(lines), _curr(0), _tokens(), _currLine(0)
{
}

Tokenizer::~Tokenizer()
{
}

void Tokenizer::Tokenize()
{
	this->_tokens.clear();
	if (this->_currLine >= this->_lines.size()) return;

	std::string& currLine = this->_lines[this->_currLine];
	while (_curr != currLine.size()) {
		if (std::isalpha(peek())) {
			std::string value = "";
			while (std::isalnum(peek())) {
				value += getAndMove();
			}

			if (value == "out") {
				this->_tokens.push_back({ TokenType::out, value });
			}
			else if (value == "set") {
				this->_tokens.push_back({ TokenType::set, ""});
			}
			else if (value == "rule") {
				this->_tokens.push_back({ TokenType::rule, ""});
			}
			else if (value == "if") {
				this->_tokens.push_back({ TokenType::_if, ""});
			}
			else {
				this->_tokens.push_back({ TokenType::var_name, value });
			}
		}
		else if (std::isdigit(peek())) {
			std::string value = "";
			while (std::isdigit(peek())) {
				value += getAndMove();
			}
			this->_tokens.push_back({ TokenType::int_lit, std::to_string(stoi(value)) });
		}
		else if (peek() == '\"') {
			std::string value = "";
			getAndMove();
			while (peek() != '\"') {
				if (peek() == '\0') break;
				value += getAndMove();
			}
			getAndMove();

			this->_tokens.push_back({ TokenType::str_lit, value });
		}
		else if (peek() == ';') {
			getAndMove();
			this->_tokens.push_back({ TokenType::semi, ""});
		}
		else if (peek() == ' ') {
			getAndMove();
		}
		else if (peek() == '=') {
			getAndMove();
			if (peek() == '=') {
				getAndMove();
				this->_tokens.push_back({ TokenType::eq, ""});
			}
			else {
				this->_tokens.push_back({ TokenType::assign, ""});
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
			this->_tokens.push_back({ TokenType::larger, ""});
		}
		else if (peek() == '<') {
			getAndMove();
			this->_tokens.push_back({ TokenType::smaller, ""});
		}
		else if (peek() == '{') {
			getAndMove();
			this->_tokens.push_back({ TokenType::open_brak, ""});
		}
		else if (peek() == '}') {
			getAndMove();
			this->_tokens.push_back({ TokenType::close_brak, ""});
		}
		else if (peek() == '(') {
			getAndMove();
			this->_tokens.push_back({ TokenType::open_par, ""});
		}
		else if (peek() == ')') {
			getAndMove();
			this->_tokens.push_back({ TokenType::close_par, ""});
		}
		else if (peek() == '\t') {
			getAndMove();
		}
		else if (peek() == '-') {
			getAndMove();
			if (peek() == '-') {
				break;
			}
			else {
				this->_tokens.push_back({ TokenType::minus, ""});
			}
		}
		else {
			std::string error = "Unrecognized Token: ` `";
			error[21] = peek();
			throw std::runtime_error(error);
		}
	}
	this->_curr = 0;
	this->_currLine++;
	_tokensSets.push_back(_tokens);
	Tokenize();
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

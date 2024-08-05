#include "parser.h"

Parser::Parser(std::vector<std::vector<Token>> tokens) :
	_curr(0), _tokens(tokens), _currLine(0)
{
}

Parser::~Parser()
{
}

void Parser::Parse()
{
	if (this->_currLine >= this->_tokens.size()) return;

	std::vector<Token>& currentTokens = _tokens[_currLine];

	while (_curr < currentTokens.size()) {
		if (stopCodeBrak > 0) {
			while (peek().tokenType != TokenType::close_brak && peek().tokenType != TokenType::eol) {
				if (peek().tokenType == TokenType::open_brak) {
					stopCodeBrak++;
				}
				getAndMove();
			}
			if (peek().tokenType == TokenType::close_brak) {
				getAndMove();
				stopCodeBrak--;
			}
			continue;
		}
		if (peek().tokenType == TokenType::out) {
			getAndMove();
			if (peek().tokenType == TokenType::str_lit || peek().tokenType == TokenType::int_lit) {
				Token tokenHolder = getAndMove();
				checkSemi();
				std::cout << tokenHolder.value << std::endl;
			}
			else if (peek().tokenType == TokenType::var_name) {
				std::string varName = getAndMove().value;
				if (this->_vars.find(varName) != this->_vars.end()) {
					checkSemi();
					std::cout << this->_vars.at(varName) << std::endl;
				}
				else {
					std::string error = "ParserError: Unkown variable `" + varName + "` at line " + std::to_string(this->_currLine + 1);
					throw std::runtime_error(error);
				}
			}
			else {
				std::string error = "ParserError: Expected string or variable name after 'out' keyword " + std::to_string(this->_currLine + 1);
				throw std::runtime_error(error);
			}
		} 
		else if (peek().tokenType == TokenType::set) {
			getAndMove();
			if (peek().tokenType == TokenType::var_name) {
				std::string varName = getAndMove().value;
				if (peek().tokenType == TokenType::assign) {
					getAndMove();
					if (peek().tokenType == TokenType::str_lit || peek().tokenType == TokenType::int_lit) {
						std::string value = getAndMove().value;
						checkSemi();
						this->_vars.insert_or_assign(varName, value);
					}
					else if (peek().tokenType == TokenType::var_name) {
						std::string assignVarName = getAndMove().value;
						if (this->_vars.find(assignVarName) != this->_vars.end()) {
							checkSemi();
							this->_vars.insert_or_assign(varName, this->_vars.at(assignVarName));
						}
						else {
							std::string error = "ParserError: Unkown variable `" + varName + "` at line " + std::to_string(this->_currLine + 1);
							throw std::runtime_error(error);
						}
					}
				}
			}
		}
		else if (peek().tokenType == TokenType::rule) {
			getAndMove();
			if (peek().tokenType == TokenType::_if) {
				getAndMove();
				if (peek().tokenType != TokenType::open_par) {
					std::string error = "ParserError: Expected `(` after if keyword " + std::to_string(this->_currLine + 1);
					throw std::runtime_error(error);
				}
				getAndMove();
				if (peek().tokenType == TokenType::var_name) {
					std::string first = getAndMove().value;
					if (this->_vars.find(first) != this->_vars.end()) {
						first = this->_vars.at(first);
					}
					else {
						std::string error = "ParserError: Unkown variable `" + first + "` at line " + std::to_string(this->_currLine + 1);
						throw std::runtime_error(error);
					}
					if (peek().tokenType == TokenType::eq || peek().tokenType == TokenType::neq || peek().tokenType == TokenType::larger || peek().tokenType == TokenType::smaller) {
						TokenType oper = getAndMove().tokenType;
						if (peek().tokenType == TokenType::var_name) {
							std::string second = getAndMove().value;
							if (peek().tokenType != TokenType::close_par) {
								std::string error = "ParserError: Expected `)` after statement " + std::to_string(this->_currLine + 1);
								throw std::runtime_error(error);
							}
							if (this->_vars.find(second) != this->_vars.end()) {
								second = this->_vars.at(second);
							}
							else {
								std::string error = "ParserError: Unkown variable `" + second + "` at line " + std::to_string(this->_currLine + 1);
								throw std::runtime_error(error);
							}
							getAndMove();
							if (peek().tokenType != TokenType::open_brak) {
								std::string error = "ParserError: Expected `{` after `)` " + std::to_string(this->_currLine + 1);
								throw std::runtime_error(error);
							}
							getAndMove();
							if (operation(first, second, oper)) {
								runCodeBrak++;
							}
							else {
								stopCodeBrak++;
							}
						}
					}
				}
			}
		}
		else if (runCodeBrak > 0 && peek().tokenType == TokenType::close_brak) {
			getAndMove();
			runCodeBrak--;
		}
		else {
			std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
			throw std::runtime_error(error);
		}
	}

	this->_curr = 0;
	this->_currLine++;
	Parse();
}

void Parser::checkSemi() {
	if (peek().tokenType != TokenType::semi) {
		if (peek().tokenType == TokenType::eol) {
			std::string error = "ParserError: Missing ';' at the end of line " + std::to_string(this->_currLine + 1);
			throw std::runtime_error(error);
		}
		else {
			std::string error = "ParserError: Unexpected token at end of line " + std::to_string(this->_currLine + 1);
			throw std::runtime_error(error);
		}
	}
	getAndMove();
}

Token Parser::peek()
{
	if (this->_curr >= this->_tokens[this->_currLine].size()) {
		return { TokenType::eol, "" };
	}
	return this->_tokens[this->_currLine][this->_curr];
}

Token Parser::getAndMove()
{
	if (this->_curr >= this->_tokens[this->_currLine].size()) {
		return { TokenType::eol, "" };
	}
	this->_curr++;
	return this->_tokens[this->_currLine][this->_curr - 1];
}

bool Parser::operation(std::string a, std::string b, TokenType op)
{
	if (op == TokenType::eq) {
		return a == b;
	}
	else if (op == TokenType::neq) {
		return a != b;
	}
	else if (op == TokenType::larger) {
		if (a.size() > b.size()) {
			return true;
		}
		else if (a.size() < b.size()) {
			return false;
		}
		else {
			int index = 0;
			while (index != a.size() - 1 && a[index] == b[index]) index++;
			return a[index] > b[index];
		}
	}
	else if (op == TokenType::smaller) {
		if (a.size() < b.size()) {
			return true;
		}
		else if (a.size() > b.size()) {
			return false;
		}
		else {
			int index = 0;
			while (index != a.size() - 1 && a[index] == b[index]) index++;
			return a[index] < b[index];
		}
	}
	else {
		return false;
	}
}


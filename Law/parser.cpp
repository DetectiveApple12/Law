#include "parser.h"

Parser::Parser() : 
	_curr(0), _tokens(), _currLine(0)
{
}

Parser::Parser(std::vector<std::vector<Token>> tokens) :
	_curr(0), _tokens(tokens), _currLine(0)
{
}

Parser::~Parser()
{
}

void Parser::parse()
{
	if (this->_currLine >= this->_tokens.size()) return;

	std::vector<Token>& currentTokens = _tokens[_currLine];

	while (peek().tokenType != TokenType::eof) {
		// Rule was not met:
		if (stopCodeBrak > 0) {
			// Run until you get to the end of line or the closing brak:
			while (peek().tokenType != TokenType::close_brak && peek().tokenType != TokenType::eof) {
				if (peek().tokenType == TokenType::open_brak) {
					stopCodeBrak++;
				}
				getAndMove();
			}
			if (peek().tokenType == TokenType::close_brak) {
				// Remove one from the stop code brak if last token is brak:
				getAndMove();
				stopCodeBrak--;
			}
			continue;
		}
		// Parse output:
		if (peek().tokenType == TokenType::out) {
			getAndMove();
			if (peek().tokenType == TokenType::str_lit || peek().tokenType == TokenType::int_lit) {
				Token tokenHolder = getAndMove();
				checkSemi();
				std::cout << tokenHolder.value.substr(1, tokenHolder.value.length() - 1) << std::endl;
			}
			else if (peek().tokenType == TokenType::minus) {
				getAndMove();
				if (peek().tokenType == TokenType::int_lit) {
					Token intLit = getAndMove();
					checkSemi();
					std::cout << "-" + intLit.value.substr(1, intLit.value.length() - 1) << std::endl;
				}
				else {
					std::string error = "ParserError: Unexpected token `-` at line " + std::to_string(this->_currLine + 1);
					throw std::runtime_error(error);
				}
			}
			else if (peek().tokenType == TokenType::var_name) {
				std::string varName = getAndMove().value;
				if (this->_vars.find(varName) != this->_vars.end()) {
					checkSemi();
					auto val = this->_vars.at(varName);
					std::cout << val.substr(1, val.length() - 1) << std::endl;
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
		// Parse variable defenition:
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
					else if (peek().tokenType == TokenType::minus) {
						getAndMove();
						if (peek().tokenType == TokenType::int_lit) {
							Token intLit = getAndMove();
							checkSemi();
							this->_vars.insert_or_assign(varName, "d-" + intLit.value.substr(1, intLit.value.length() - 1));
						}
						else {
							std::string error = "ParserError: Unexpected token `-` at line " + std::to_string(this->_currLine + 1);
							throw std::runtime_error(error);
						}
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
					else {
						std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
						throw std::runtime_error(error);
					}
				}
				else {
					std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
					throw std::runtime_error(error);
				}
			}
			else {
				std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
				throw std::runtime_error(error);
			}
		}
		// Parse input:
		else if (peek().tokenType == TokenType::in) {
			getAndMove();
			if (peek().tokenType == TokenType::var_name) {
				std::string varName = getAndMove().value;
				std::string value;
				std::getline(std::cin, value);
				checkSemi();
				this->_vars.insert_or_assign(varName, "s" + value);
			}
			else {
				std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
				throw std::runtime_error(error);
			}
		}
		// Parse rules:
		else if (peek().tokenType == TokenType::rule) {
			getAndMove();
			if (peek().tokenType == TokenType::_if) {
				getAndMove();
				if (peek().tokenType != TokenType::open_par) {
					std::string error = "ParserError: Expected `(` after if keyword " + std::to_string(this->_currLine + 1);
					throw std::runtime_error(error);
				}
				getAndMove();
				if (peek().tokenType == TokenType::var_name || peek().tokenType == TokenType::str_lit || peek().tokenType == TokenType::int_lit || peek().tokenType == TokenType::minus) {
					Token token = getAndMove();
					std::string first;
					if (token.tokenType == TokenType::var_name) {
						first = token.value;
						if (this->_vars.find(first) != this->_vars.end()) {
							first = this->_vars.at(first);
						}
						else {
							std::string error = "ParserError: Unkown variable `" + first + "` at line " + std::to_string(this->_currLine + 1);
							throw std::runtime_error(error);
						}
					}
					else if (token.tokenType == TokenType::minus) {
						if (peek().tokenType == TokenType::int_lit) {
							Token intLit = getAndMove();
							first = "d-" + intLit.value.substr(1, intLit.value.length() - 1);
						}
						else {
							std::string error = "ParserError: Unexpected token `-` at line " + std::to_string(this->_currLine + 1);
							throw std::runtime_error(error);
						}
					}
					else {
						first = token.value;
					}
					if (peek().tokenType == TokenType::eq || peek().tokenType == TokenType::neq || peek().tokenType == TokenType::larger || peek().tokenType == TokenType::smaller) {
						TokenType oper = getAndMove().tokenType;
						if (peek().tokenType == TokenType::var_name || peek().tokenType == TokenType::str_lit || peek().tokenType == TokenType::int_lit || peek().tokenType == TokenType::minus) {
							token = getAndMove();
							if (peek().tokenType != TokenType::close_par && (peek().tokenType == TokenType::minus && peekTwo().tokenType != TokenType::close_par)) {
								std::string error = "ParserError: Expected `)` after statement " + std::to_string(this->_currLine + 1);
								throw std::runtime_error(error);
							}
							std::string second;
							if (token.tokenType == TokenType::var_name) {
								second = token.value;
								if (this->_vars.find(second) != this->_vars.end()) {
									second = this->_vars.at(second);
								}
								else {
									std::string error = "ParserError: Unkown variable `" + first + "` at line " + std::to_string(this->_currLine + 1);
									throw std::runtime_error(error);
								}
							}
							else if (token.tokenType == TokenType::minus) {
								if (peek().tokenType == TokenType::int_lit) {
									Token intLit = getAndMove();
									second = "d-" + intLit.value.substr(1, intLit.value.length() - 1);
								}
								else {
									std::string error = "ParserError: Unexpected token `-` at line " + std::to_string(this->_currLine + 1);
									throw std::runtime_error(error);
								}
							}
							else {
								second = token.value;
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
						else {
							std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
							throw std::runtime_error(error);
						}
					}
					else {
						std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
						throw std::runtime_error(error);
					}
				}
				else {
					std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
					throw std::runtime_error(error);
				}
			}
			else {
				std::string error = "ParserError: Unexpected token at line " + std::to_string(this->_currLine + 1);
				throw std::runtime_error(error);
			}
		}
		// Parse close braks:
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
	parse();
}

void Parser::updateTokens(std::vector<std::vector<Token>> tokens)
{
	this->_tokens = tokens;
	this->_curr = 0;
	this->_currLine = 0;
}

void Parser::checkSemi() {
	if (peek().tokenType != TokenType::semi) {
		std::string error = "ParserError: Missing ';' at the end of line " + std::to_string(this->_currLine + 1);
		throw std::runtime_error(error);
	}
	getAndMove();
}

Token Parser::peek()
{
	if (this->_curr >= this->_tokens[this->_currLine].size()) {
		if (this->_currLine + 1 >= this->_tokens.size()) {
			return { TokenType::eof, "" };
		}
		this->_currLine++;
		this->_curr = 0;
		return peek();
	}
	return this->_tokens[this->_currLine][this->_curr];
}

Token Parser::peekTwo() {
	if (this->_curr + 1 >= this->_tokens[this->_currLine].size()) {
		if (this->_currLine + 1 >= this->_tokens.size()) {
			return { TokenType::eof, "" };
		}
		return this->_tokens[this->_currLine + 1][0];
	}
	return this->_tokens[this->_currLine][this->_curr + 1];
}

Token Parser::getAndMove()
{
	if (this->_curr >= this->_tokens[this->_currLine].size()) {
		if (this->_currLine + 1 >= this->_tokens.size()) {
			return { TokenType::eof, "" };
		}
		this->_currLine++;
		this->_curr = 0;
		return getAndMove();
	}
	this->_curr++;
	return this->_tokens[this->_currLine][this->_curr - 1];
}

bool isInteger(std::string string)
{
    auto i = string.begin();
    while (i != string.end() && (std::isdigit(*i) || *i == '-')) ++i;
    return !string.empty() && i == string.end();
}

bool Parser::operation(std::string a, std::string b, TokenType op)
{
	if (a[0] != 'd' && b[0] == 'd' || a[0] == 'd' && b[0] != 'd' || a[0] == 'd' && a[0] == 'd') {
		int aInt = 0, bInt = 0;
		if (a[0] == 'd' || isInteger(a.substr(1, a.length() - 1))) {
			aInt = stoi(a.substr(1, a.length() - 1));
		} if (b[0] == 'd' || isInteger(b.substr(1, b.length() - 1))) {
			bInt = stoi(b.substr(1, b.length() - 1));
		}

		if (op == TokenType::eq) {
			return aInt == bInt;
		}
		else if (op == TokenType::neq) {
			return aInt != bInt;
		}
		else if (op == TokenType::larger) {
			return aInt > bInt;
		}
		else if (op == TokenType::smaller) {
			return aInt < bInt;
		}
		else {
			return false;
		}
	}
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


#ifndef LEXER_H
#define LEXER_H

#include <fstream>
#include <string>
#include <vector>

#include <iostream> // only to test print tokens

enum class Token_Type {
	Command,		// add del
	Identifier,		// name
	Argument		// inside ()
};

struct Token
{
	Token() = delete;
	Token(Token_Type t, std::string n)
		: type(t)
		, name(n)
	{};

	Token_Type type;
	std::string name;
};

void Tokenizer(std::istream& in_stream, std::vector<Token*>& tokens);

void printTokens(std::vector<Token*>& tokens);

#endif // LEXER_H

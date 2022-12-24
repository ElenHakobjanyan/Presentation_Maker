#include "Parser.h"


char SkipCommentsAndSpaces(std::istream& in_stream)
{
	char c = in_stream.peek();

	if (c == '#')
	{
		while (c != '\n' && !in_stream.eof())
		{
			c = in_stream.get();
		}
		return SkipCommentsAndSpaces(in_stream);
	}

	if (c == ' ' || c == '\n')
	{
		char prev_ch = c;
		while (c == ' ' || c == '\n')
		{
			c = in_stream.get();
			c = in_stream.peek();
		}
		return prev_ch;
	}

	return in_stream.get();
}

std::string ParseLexeme(std::istream& in_stream, char& is_p)
{
	std::string sWord = "";

	char c;
	is_p = ' ';

	while (!in_stream.eof())
	{
		c = SkipCommentsAndSpaces(in_stream);

		if (c == '"')
		{
			while (!in_stream.eof())
			{
				c = SkipCommentsAndSpaces(in_stream);
				if (c == '"') return std::move(sWord);
				sWord += c;
			}
		}
		else if (c == ' ' || c == '\n' || c == ',') break;
		else if (c == '(' || c == ')')
		{
			is_p = c;
			break;
		}
		sWord += c;
	}

	return std::move(sWord);
}

bool isCommand(std::string lexemme)
{
	if (lexemme == "new" || lexemme == "edit" || lexemme == "add" || lexemme == "del" || lexemme == "save" || lexemme == "exit" || lexemme == "print")
	{
		return true;
	}
	return false;
}

void Tokenizer(std::istream& in_stream, std::vector<Token*>& tokens)
{
	bool inParentheses = false;
	char is_p;
	do
	{
		std::string Lexemme = ParseLexeme(in_stream, is_p);
	
		if (Lexemme != "" && !in_stream.eof())
		{
			Token_Type type = Token_Type::Identifier;
			
			
			if (isCommand(Lexemme))
			{
				type = Token_Type::Command;
				inParentheses = false;

			}
			else if (inParentheses)
			{
				type = Token_Type::Argument;
			}

			Token* t = new Token(type, Lexemme);
			tokens.push_back(t);

			if (is_p == '(')
			{
				inParentheses = true;
			}
			else if (is_p == ')')
			{
				inParentheses = false;
			}
		}
	} while (!in_stream.eof());

}

void printTokens(std::vector<Token*>& tokens)
{
	for (auto t : tokens)
	{
		if (t->type == Token_Type::Command)
		{
			std::cout << t->name << ": Command\n";
		}
		else if (t->type == Token_Type::Argument)
		{
			std::cout << t->name << ": Argument\n";
		}
		else if (t->type == Token_Type::Identifier)
		{
			std::cout << t->name << ": Identifier\n";
		}
	}
}
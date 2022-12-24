#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Parser.h"
#include "cmd.h"

int main() 
{

	std::string path = "cmd_file.txt";

	std::fstream cmd_file(path);

	if (!cmd_file)
	{
		std::cout << "File(" << path << ") open error.\n";
	}

	std::vector<Token*> tokens;

	Tokenizer(cmd_file, tokens);
	printTokens(tokens);


	cApp* obApp = cApp::getInstance();

	fill_cmds(tokens);
	obApp->execute();

	return 0;
}
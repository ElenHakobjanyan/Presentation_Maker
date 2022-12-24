#include "cmd.h"


cApp* cApp::getInstance()
{
	if (instancePtr == nullptr)
	{
		instancePtr = new cApp();
	}

	return instancePtr;
}

void addCommand(cCommand* cmd)
{
	this->m_commands.push_back(cmd);
}

void addCommandToHistory(cCommand* cmd)
{
	this->m_cmd_history.push_back(cmd);
}

void cApp::execute()
{
	for (auto cmd : this->m_commands)
	{
		cmd->Exec();
		addCommandToHistory(cmd);
	}
}

cApp* cApp::instancePtr = nullptr;


class cCommand
{
public:

	cCommand(Token* name)
		: m_cmd_name(name)
	{}

	void setId(Token* id)
	{
		this->m_id = id;
	}

	void addArg(Token* arg)
	{
		m_args.push_back(arg);
	}

	void Exec()
	{
		std::cout << "cmd executed\n";
		// add to history
	}


private:
	Token* m_cmd_name;
	Token* m_id;
	std::vector<Token*> m_args;
};

void fill_cmds(std::vector<Token*> tokens)
{
	cCommand* curr = nullptr;

	for (auto t : tokens)
	{
		switch (t->type)
		{
		case Token_Type::Command:
			if (curr) cApp::getInstance()->addCommand(curr);
			curr = new cCommand(t);
			break;
		case Token_Type::Identifier:
			curr->setId(t);
			break;
		case Token_Type::Argument:
			curr->addArg(t);
			break;
		}
	}
}

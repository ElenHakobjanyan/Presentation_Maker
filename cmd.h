#ifndef CMD_H
#define CMD_H

#include <vector>
#include "Parser.h"


class cCommand
{
public:

    cCommand(Token* name);

    void setId(Token* id);

    void addArg(Token* arg);

    void Exec();


private:
    Token* m_cmd_name;
    Token* m_id;
    std::vector<Token*> m_args;
};

class cApp {
public:
    cApp(const cApp& obj) = delete;

    static cApp* getInstance();

    void addCommand(cCommand* );

    void addCommandToHistory(cCommand* );

    void execute();

private:
    std::vector<cCommand*> m_commands;
    std::vector<cCommand*> m_cmd_history; // make circular buffer
    static cApp* instancePtr;

    //std::string m_presentation_name;

    cApp() {};
};




void fill_cmds(std::vector<Token*> tokens);


#endif // CMD_H

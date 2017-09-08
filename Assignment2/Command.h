//
// Created by kcmmac on 2017-06-02.
//

#ifndef KCMASSIGN2_COMMAND_H
#define KCMASSIGN2_COMMAND_H

#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

// * A class that parse the command and store the parsing result to its properties. *

class Command {

private:
    int start_line;
    int end_line;

    bool command_valid;
    string msg;

    void removeWS(string& );
    void removeTabs(string& );
    char symbol;

    bool is_digit(const string&);

    void parseSubString(string, int, int, int);

public:

    Command();
    virtual ~Command();

    void parse(string command_line, int current_line, int last_line);

    bool isCommand_valid() const;
    const string &getMsg() const;
    const char getSymbol();

    int getStart_line() const;
    int getEnd_line() const;
};


#endif //KCMASSIGN2_COMMAND_H

//
// Created by kcmmac on 2017-06-02.
//


#include "Command.h"

using namespace std;

Command::Command()
{
    start_line = 0;
    end_line = 0;
}

Command::~Command(){}

// parse the given command and store the result to the object's properties.
void Command::parse(string command_line, int current_line, int last_line)
{
    command_valid = true;

	if( command_line.length() < 1 ){
        symbol = 'd';
        start_line = 1;
        end_line = start_line;
        return;
    }

    //remove all white spaces
    removeWS(command_line);
    removeTabs(command_line);

    int len = command_line.length();

    char ch = command_line.at(len-1);	// take the last letter.
    string nstr;
    size_t found;


    if( isdigit(ch) )		// if the last letter is a digit,
    {
        symbol = 'p';
        nstr = command_line;
        
        found = nstr.find(",");
        if (found == string::npos){
            start_line = stoi(nstr);
            end_line = start_line;
        }

    } else {				//not digit
        if( ch == ',' || ch == '.'  ){
            symbol = 'p';
            nstr = command_line.substr(0, len - 1);

        } else if ( ch == '$' ) {
            symbol = 'p';
            nstr = command_line.substr(0, len);

        } else{
            if( ch == 'a' || ch == 'i' || ch == 'r' || ch == 'p' || ch == 'n' || ch == 'c' || ch == 'u'
                  || ch == 'd' || ch == 'w' || ch == '=' || ch == 'q' )
            {
                symbol = ch;
                nstr = command_line.substr(0, len - 1);
            } else {
                command_valid = false;
            }

        }

        found = nstr.find(",");

        if (found == string::npos){
            if(nstr.length() > 0 )
            {
                if( is_digit( nstr ) ){
                    start_line = stoi(nstr);
                    if( ch == ','){
                        end_line = current_line;
                    } else {
                        end_line = start_line;
                    }

                } else {
                    char newCh = nstr.at(0);
                    if( newCh == '.'){
                        start_line = current_line;
                    } else if ( newCh == '$'){
                        start_line = last_line;
                    } else {
                        command_valid = false;
                    }
                    end_line = start_line;

                }

            } else {
                if( ch == 'd' || ch == 'u')
                {
                    start_line = 1;

                }else if ( ch == '$') {
                    start_line = last_line;

                }else{
                    start_line = current_line;

                }
                end_line = start_line;

            }

        }

    }//isdigit(ch)


    if ( found != string::npos)    // if a comma exists
    {
        string s1 = nstr.substr(0, found);
        string s2 = nstr.substr(found + 1, nstr.length());

        size_t found2 = s2.find(",");
        if (found2  !=  string::npos )        // more commas
        {
            command_valid = false;
        }

        parseSubString(s1, current_line, last_line, 0);
        parseSubString(s2, current_line, last_line, 1);

    }

    if(!command_valid)
	{
        ostringstream sout;
        sout <<  "invalid line address: " << command_line << endl;
        msg =  sout.str() ;
    }

}

// parseSubString(): parsing subsequent strings.
void Command::parseSubString(string s1, int current_line, int last_line, int mode)
{
    int tline = 0;

    if (s1.length() > 0)
    {
        if (is_digit(s1)) {
            tline = stoi(s1);
        } else
        {
            if (s1.length() > 1)
            {
                command_valid = false;
            } else
            {
                char tch = s1.at(0);
                if (tch == '.') {
                    tline = current_line;
                } else if(tch == '$') {
                    tline = last_line;
                } else {
                    command_valid = false;
                }

            }
        }

    } else
    {
        tline = current_line;
    }

    if(mode == 0){
        start_line = tline;
    } else{
        end_line = tline;
    }

}

bool Command::is_digit(const string & str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

void Command::removeWS(string & str)
{
    str.erase( remove(str.begin(), str.end(), ' '), str.end() );
}

void Command::removeTabs(string & str)
{
    str.erase( remove(str.begin(), str.end(), '\t'), str.end() );
}

const char Command::getSymbol()
{
    return symbol;
}

bool Command::isCommand_valid() const {
    return command_valid;
}

const string &Command::getMsg() const {
    return msg;
}

int Command::getStart_line() const {
    return start_line;
}

int Command::getEnd_line() const {
    return end_line;
}

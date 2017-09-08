//
// Created by kcmmac on 2017-06-02.
//

#ifndef KCMASSIGN2_LED_H
#define KCMASSIGN2_LED_H

#include <list>
#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include "Command.h"

using namespace std;

// * A class that implements functions as an editor.*
// - funstions : add/remove/change the string, move up/down the current position.

class Led {

private:
	// a data structure that stores strings written
    list<string> buffer;

    int current_line;
    int last_line;

    string filename;

    bool is_file_editted;

    void append_line(int pos);
    void print(int istart, int iend, int mode);
    void remove_line(int istart, int iend);
    void quit();
    void writeToFile();
    void print_curline_addr();
    void change_txt2txt(int istart, int iend);
    void move_up(int offset);
    void move_down(int offset);
	
    void execute(Command&);

    void print_n_line(int line_num);
    bool is_line_exist();
	bool is_valid_range(int, int);

public:
    Led();
    Led(const string&);

	// start the editor.
    void run();


};

#endif //KCMASSIGN2_LED_H
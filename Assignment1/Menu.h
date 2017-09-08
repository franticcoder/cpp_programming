//
// Created by Chungmin Kim on 2017-05-10.
//

#ifndef AS1_MENU_H
#define AS1_MENU_H

#include <sstream>
#include <iostream>
#include "Text.h"

using namespace std;

class Menu
{
private:
    Text *option_list;
    int count;
    int max_list_size;

    Text top_prompt;
    Text bottom_prompt;
    Text top_text;
    Text bottom_text;

    const char* literal = "?-> ";

    void double_capacity();

public:
    Menu();
    Menu( const Menu& );
    virtual ~Menu();

    Menu& operator=(const Menu&);
    void insert(int, const Text&);

    void push_back( char* );
    void push_back(const Text&);
    Text remove(int);


    int size();
    int capacity();

    void pop_back();
    Text get(int);
    Text toString() const ;

    int read_option_number();

    void set_top_prompt(const Text&);
    void set_bottom_prompt(const Text&);
    void set_top_message(const Text&);
    void set_bottom_message(const Text&);

    void clear_top_prompt();
    void clear_bottom_prompt();
    void clear_top_message();
    void clear_bottom_message();

    bool isEmpty() const;

    friend ostream& operator<<(ostream&, const Menu& );
};

#endif //AS1_MENU_H
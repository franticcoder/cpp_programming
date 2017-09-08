//
// Created by Chungmin Kim on 2017-05-10.
//


#ifndef AS1_TEXT_H
#define AS1_TEXT_H

#include <iostream>
#include <cstring>

using namespace std;

class Text
{

private:
    char *text;

public:

    virtual ~Text();

    Text();
    Text(const Text&);
    Text(const char*);

    void set(char *);
    void set(const Text&);

    Text& operator=(const Text& );

    friend ostream& operator<<(ostream&, const Text& );

    void append(const char*);
    void append(const Text&);

    int length() const;
    bool isEmpty() const;

};

#endif //AS1_TEXT_H
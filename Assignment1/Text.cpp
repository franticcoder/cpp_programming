//
// Created by kcmmac on 2017-05-10.
//


#include "Text.h"


//default constructor
Text::Text() : Text("") { }

//destructor
Text::~Text()
{
    delete [] text;
}


//copy constructor
Text::Text(const Text& t)
{
    int len = strlen(t.text);
    text = new char[len+1];

	//copy the string
    strcpy(text, t.text);

}

//conversion constructor
Text::Text(const char* t)
{
    int len = strlen(t);
    text = new char[len+1];

    strcpy(text,t);

}

//set a string(char*) to Text object
void Text::set(char* t)
{
    int len = strlen(t);
    delete [] text;

    text = new char[len+1];
    strcpy(text, t);

}

//set a string(Text&) to Text object
void Text::set(const Text& t)
{
    int len = strlen(t.text);
    delete [] text;

    text = new char[len+1];
    strcpy(text, t.text);
}

// overloading of operator=
Text& Text::operator=(const Text& t)
{
    // in case of the same object, return itself.
	if(this == &t)  return *this;

    delete [] text;

    int len = strlen(t.text);
    text = new char[len+1];
    strcpy(text, t.text);

    return *this;
}


// overloading operator<< 
ostream& operator<<(ostream& out, const Text& t)
{
    out << t.text;
    return out;
}


// append the given string(char*) to the existing 'text'
void Text::append(const char* t )
{
    int len1 = strlen(text);
    int len2 = strlen(t);

    char *tmpText = new char[len1+len2+1];

    strcpy(tmpText,text);
    strcat(tmpText, t);

    delete [] text;
    text = tmpText;

}

// append the given string(Text&) to the existing 'text'
void Text::append(const Text& t)
{
    int len1 = strlen(text);
    int len2 = strlen(t.text);

	// allocate new storage.
    char *tmpText = new char[len1+len2+1];

    strcpy(tmpText,text);		// copy its own part.
    strcat(tmpText, t.text);	// concatenate the new part.
    delete [] text;
    text = tmpText;

}


// return the length of 'text' member variable
int Text::length() const
{
    return strlen(text);
}

// return true/false if the string is empty
bool Text::isEmpty() const
{
    return (text == nullptr || length() == 0);
}
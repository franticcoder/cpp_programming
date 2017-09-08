//
// Created by kcmmac on 2017-07-11.
//

#ifndef KCMASSIGN4_SHAPE_H
#define KCMASSIGN4_SHAPE_H

#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// * The base class of derived classes, which contains basic information about the shape. *

class Shape {

public:

	Shape() = delete;	// not use default ctor
    Shape(const string&, const string&);
    virtual ~Shape();


    int getIdnum() const;

    const string &getGeneric_name() const;
    const string &getDescriptive_name() const;

    void setDescriptive_name(const string &descriptive_name);

    virtual vector<vector<char>> draw(char penChar='*', char fillChar = ' ') const = 0;

    void draw_on_screen(char penChar='*', char fillChar = ' ') const;
    void write_image_to_screen(ostream& out, char );
    void write_image_to_screen(ostream& out, char, char );
	string toString() const;

	// *** virtual methods ***
    virtual void scale(int) = 0;
    virtual int bounding_box_height() const = 0;
    virtual int bounding_box_width() const = 0;
    virtual int scr_area() const = 0;
    virtual double geo_area() const = 0;
    virtual int scr_perimeter() const = 0;
    virtual double geo_perimeter() const = 0;

protected:

    int idnum;
    string generic_name;
    string descriptive_name;

	friend ostream& operator<<(ostream& sout, const vector<vector<char>> &grid);
	friend ostream& operator<<(ostream& sout, const Shape&);


private:
    static int next_id;

};



#endif //KCMASSIGN4_SHAPE_H

//
// Created by kcmmac on 2017-07-11.
//

#ifndef KCMASSIGN4_RECTANGLE_H
#define KCMASSIGN4_RECTANGLE_H

#include <iostream>
#include <vector>

#include "Shape.h"


class Rectangle : public Shape {


public:
	Rectangle() = delete;
    Rectangle(int, int, const string& dn = "Generic Rectangle");
    ~Rectangle();

    vector<vector<char>> draw(char penChar='*', char fillChar=' ') const override ;

    void scale(int) override ;

    int bounding_box_height() const  override ;
    int bounding_box_width() const  override ;
    int scr_area() const override ;
    double geo_area() const override ;
    int scr_perimeter() const override ;
    double geo_perimeter() const override ;


private:

	size_t width;
	size_t height;

};


#endif //KCMASSIGN4_RECTANGLE_H

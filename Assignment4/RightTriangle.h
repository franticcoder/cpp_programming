//
// Created by kcmmac on 2017-07-11.
//

#ifndef KCMASSIGN4_RIGHTTRIANGLE_H
#define KCMASSIGN4_RIGHTTRIANGLE_H

#include <vector>
#include "Triangle.h"


class RightTriangle : public Triangle {


public:
	RightTriangle() = delete;
    RightTriangle(int, const string& dn = "Generic RightTriangle");
    ~RightTriangle();

    vector<vector<char>> draw(char penChar='*', char fillChar=' ') const override ;

    void scale(int) override ;

    int bounding_box_height() const  override ;
    int bounding_box_width() const  override ;
    int scr_area() const override ;
    double geo_area() const override ;
    int scr_perimeter() const override ;
    double geo_perimeter() const override ;


private:

};

#endif //KCMASSIGN4_RIGHTTRIANGLE_H

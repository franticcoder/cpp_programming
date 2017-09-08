//
// Created by kcmmac on 2017-07-11.
//

#ifndef KCMASSIGN4_ISOSCELES_H
#define KCMASSIGN4_ISOSCELES_H

#include "Triangle.h"
#include <vector>

class Isosceles : public Triangle {

public:

	Isosceles() = delete;
    Isosceles(int base, const string& dn =  "Generic Isosceles");
    ~Isosceles();

    vector<vector<char>> draw(char penChar='*', char fillChar=' ') const override ;

    void scale(int) override ;

    int bounding_box_height() const  override ;
    int bounding_box_width() const  override ;
    int scr_area() const override ;
    double geo_area() const override ;
    int scr_perimeter() const override ;
    double geo_perimeter() const override ;


protected:


private:


};

#endif //KCMASSIGN4_ISOSCELES_H

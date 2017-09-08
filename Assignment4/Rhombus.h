//
// Created by kcmmac on 2017-07-11.
//

#ifndef KCMASSIGN4_RHOMBUS_H
#define KCMASSIGN4_RHOMBUS_H


#include "Shape.h"

class Rhombus : public Shape {

public:
	Rhombus() = delete;
    Rhombus(int, const string& dn = "Generic Rhombus");
    ~Rhombus();
    vector<vector<char>> draw(char penChar='*', char fillChar=' ') const override ;

    void scale(int) override ;


    int bounding_box_height() const  override ;
    int bounding_box_width() const  override ;
    int scr_area() const override ;
    double geo_area() const override ;
    int scr_perimeter() const override ;
    double geo_perimeter() const override ;


private:
	size_t diagonal;


};

#endif //KCMASSIGN4_RHOMBUS_H

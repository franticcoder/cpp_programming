//
// Created by kcmmac on 2017-07-11.
//

#ifndef KCMASSIGN4_TRIANGLE_H
#define KCMASSIGN4_TRIANGLE_H

#include "Shape.h"

class Triangle  : public Shape {

public:
    Triangle(int, int, const string& , const string&);
    virtual ~Triangle();

protected:
    size_t base;
	size_t height;


private:

};

#endif //KCMASSIGN4_TRIANGLE_H

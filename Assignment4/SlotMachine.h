//
// Created by kcmmac on 2017-07-13.
//

#ifndef KCMASSIGN4_SLOTMACHINE_H
#define KCMASSIGN4_SLOTMACHINE_H

#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Shape.h"
#include "Rhombus.h"
#include "Isosceles.h"
#include "Rectangle.h"
#include "RightTriangle.h"


using namespace std;

// * A class that provides functions of a simple SlotMachine  *

class SlotMachine {

private:

    int token;
    int bet_token;

    array<Shape*, 3> shape_reel;

    void make_shapes();

    void make_shape(int );

    void display_shapes();

    void report_status();

    void release_shapes();

    void display_intro();

    int get_rnd_num(int , int);

public:

    SlotMachine() = default;

    SlotMachine(const SlotMachine& ) = delete;
    SlotMachine& operator=(const SlotMachine& ) = delete;

    void run();
    virtual ~SlotMachine();


};

#endif //KCMASSIGN4_SLOTMACHINE_H

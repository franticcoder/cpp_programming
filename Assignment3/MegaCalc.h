//
// Created by kcmmac on 2017-06-26.
//

#ifndef KCMASSIGN3_MEGACALC_H
#define KCMASSIGN3_MEGACALC_H

#include <iostream>
#include <string>
#include <algorithm>
#include "MegaInt.h"

class MegaCalc {

private:
    MegaInt valAcc;

	void hailstone(MegaInt);
	MegaInt factorial(const MegaInt&);

	void removeWS(string&);
	void removeTabs(string&);

	bool is_digit(string&);

public:

    MegaCalc();
    void run();

};

#endif //KCMASSIGN3_MEGACALC_H

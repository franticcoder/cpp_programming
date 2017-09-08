//
// Created by kcmmac on 2017-08-04.
//

#ifndef KCMASSIGN5_MYCOMPARE_H
#define KCMASSIGN5_MYCOMPARE_H

#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// * 

class MyCompare {

public:

	// overloaded functino call operator
    bool operator()(const string & , const string & ) const;

};

#endif //KCMASSIGN5_MYCOMPARE_H

//
// Created by kcmmac on 2017-08-04.
//

#include "MyCompare.h"

// operator()() : convert the given string to capital letters and compare them.
bool MyCompare::operator()(const string& first, const string &second) const {
    string s1{first};
    string s2{second};

	// transform the given string to capital letters.
    std::transform(s1.begin(), s1.end(), s1.begin(), ::toupper);
    std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);

    return s1 < s2;

}
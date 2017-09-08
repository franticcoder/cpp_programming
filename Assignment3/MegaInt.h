//
// Created by kcmmac on 2017-06-26.
//

#ifndef KCMASSIGN3_MEGAINT_H
#define KCMASSIGN3_MEGAINT_H

#include <iostream>
#include <sstream>
#include <deque>

using namespace std;

// * A class that provides functions of a giant integer, which is way bigger than normal integer. *
// - functions: arithmetic calculation, comparison, increment, decrement and etc.

class MegaInt {

	// operator overloading as friend.
    friend ostream& operator<<(ostream&, MegaInt& );
    friend bool operator>(const MegaInt& , const MegaInt& );
	friend bool operator>=(const MegaInt&, const MegaInt&);
    friend bool operator<(const MegaInt& , const MegaInt& );
	friend bool operator<=(const MegaInt&, const MegaInt&);
	friend bool operator==(const MegaInt&, const MegaInt&);
	friend bool operator!=(const MegaInt&, const MegaInt&);

private:

    void copyToThis(const MegaInt&);

	MegaInt plus(const MegaInt&, const MegaInt&);
	MegaInt minus(const MegaInt&, const MegaInt&);
	MegaInt subMultiply(const MegaInt&, int, int&);

	void normalize(MegaInt&);
	
	void megaInt2string(const MegaInt&, string&);

public:
    deque<char> mega_int;
    bool mega_sign;

	MegaInt(string);
    MegaInt();
    ~MegaInt();
    MegaInt(const MegaInt&);

    MegaInt& operator=(const MegaInt& );

	MegaInt operator+(const MegaInt&);
	MegaInt operator-(const MegaInt&);
	MegaInt operator*(const MegaInt&);
	MegaInt operator/(const MegaInt&);
	MegaInt operator%(const MegaInt&);

	MegaInt& operator+=(const MegaInt&);
	MegaInt& operator-=(const MegaInt&);
	MegaInt& operator*=(const MegaInt&);
	MegaInt& operator/=(const MegaInt&);
	MegaInt& operator%=(const MegaInt&);

	MegaInt& operator++();		//prefix
	MegaInt& operator--();

	MegaInt operator++(int);	//postfix
	MegaInt operator--(int);
	
	const int operator[](int) const;

	MegaInt add(const MegaInt&, const MegaInt&);
	MegaInt subtract(const MegaInt&, const MegaInt&);
	MegaInt multiply(const MegaInt&, const MegaInt&);
	MegaInt divide(MegaInt, MegaInt, int);

};
#endif //KCMASSIGN3_MEGAINT_H

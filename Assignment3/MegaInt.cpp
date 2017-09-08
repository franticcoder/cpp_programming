//
// Created by kcmmac on 2017-06-26.
//

#include "MegaInt.h"


MegaInt::MegaInt() : MegaInt("") {}

MegaInt::~MegaInt() {}

//copy ctor
MegaInt::MegaInt(const MegaInt& mi) {
    copyToThis(mi);
}

// conversion ctor
MegaInt::MegaInt(string inStr)
{
    int i_st = 0;

    if(inStr.length() > 1){
        char ch0 = inStr.at(0);
        if ( ch0 == '+') {
            mega_sign = false;
            i_st = 1;
        }else if ( ch0 == '-'){
            mega_sign = true;
            i_st = 1;
        }else{
            mega_sign = false;
        }
    }else{
        mega_sign = false;
    }

    char tch;
    for(size_t k = i_st; k < inStr.length() ;  k++){
        tch = inStr.at(k);
        mega_int.push_back( tch );
    }
}


MegaInt& MegaInt::operator=(const MegaInt& mi)
{
    copyToThis(mi);
    return *this;
}

// copyToThis() : copy the given value to the object's itself.
void MegaInt::copyToThis(const MegaInt& mi)
{
    this->mega_sign = mi.mega_sign;

    this->mega_int.clear();
    char ch;
    bool isFirst = true;

    deque<char>::const_iterator it = mi.mega_int.begin();

    while ( it != mi.mega_int.end() ){

        if(isFirst) {
            if ( *it == '+') {
                this->mega_sign = false;
            } else if ( *it == '-') {
                this->mega_sign = true;
            } else {
                ch = *it;
                this->mega_int.push_back( ch );
            }
            isFirst = false;
            *it++;
            continue;
        }
        ch = *it++;
        this->mega_int.push_back( ch );
    }
}

ostream& operator<<(ostream& out, MegaInt& mi)
{
    ostringstream sout;
    if(mi.mega_sign){
        sout << "-";
    }else{
        sout << "+";
    }
    deque<char>::iterator it = mi.mega_int.begin();
    while( it != mi.mega_int.end() ){
        sout << *it++;
    }
    out << sout.str();

    return out;
}


const int MegaInt::operator[](int k) const
{
    return static_cast<int>(this->mega_int.at(k) - '0');
}


bool operator>(const MegaInt& lhs, const MegaInt& rhs)
{
	size_t sz_l = lhs.mega_int.size();
	size_t sz_r = rhs.mega_int.size();

	if (sz_l > sz_r){
		return true;
	}else if (sz_l < sz_r){
		return false;
	}

	size_t min_len = sz_l;	//anyone

	for (size_t k = 0; k < min_len; k++){
		if (lhs.mega_int.at(k) > rhs.mega_int.at(k)){
			return true;
		}
		else if (lhs.mega_int.at(k) < rhs.mega_int.at(k)){
			return false;
		}
	}
	
	return false;
}

bool operator<(const MegaInt& lhs, const MegaInt& rhs)
{
    return rhs > lhs;
}


bool operator==(const MegaInt& lhs, const MegaInt& rhs)
{
	size_t sz_l = lhs.mega_int.size();
	size_t sz_r = rhs.mega_int.size();

	if (sz_l != sz_r || lhs.mega_sign != rhs.mega_sign){
		return false;
	}
	size_t min_len = sz_l;

	for (size_t k = 0; k < min_len; k++){
		if (lhs.mega_int.at(k) != rhs.mega_int.at(k)){
			return false;
		}
	}

	return true;
}

bool operator>=(const MegaInt& lhs, const MegaInt& rhs)
{
	return !(lhs < rhs);
}

bool operator<=(const MegaInt& lhs, const MegaInt& rhs)
{
	return !(lhs > rhs);
}


bool operator!=(const MegaInt& lhs, const MegaInt& rhs)
{
	return !(lhs == rhs);
}


MegaInt& MegaInt::operator+=(const MegaInt& m)
{
	*this = *this + m;
	return *this;
}

MegaInt& MegaInt::operator-=(const MegaInt& m)
{
	*this = *this - m;
	return *this;
}

MegaInt& MegaInt::operator*=(const MegaInt& m)
{
	*this = *this * m;
	return *this;
}


MegaInt& MegaInt::operator/=(const MegaInt& m)
{
	*this = *this / m;
	return *this;
}


MegaInt& MegaInt::operator%=(const MegaInt& m)
{
	*this = *this % m;
	return *this;
}


MegaInt MegaInt::operator+(const MegaInt& m)
{
	return this->add(*this, m);
}


MegaInt MegaInt::operator-(const MegaInt& m)
{
	return this->subtract(*this, m);
}

MegaInt MegaInt::operator*(const MegaInt& m)
{
	return this->multiply(*this, m);
}

MegaInt MegaInt::operator/(const MegaInt& m){
	return this->divide(*this, m, 1);
}

MegaInt MegaInt::operator%(const MegaInt& m)
{
	return this->divide(*this, m, 2);
}


MegaInt& MegaInt::operator++()
{
	MegaInt one{ "1" };
	*this += one;
	return *this;
}

MegaInt& MegaInt::operator--()
{
	MegaInt one{ "1" };
	*this -= one;
	return *this;

}

MegaInt MegaInt::operator++(int)
{
	MegaInt one{ "1" };
	MegaInt tmp{ *this };
	*this += one;
	return tmp;
}

MegaInt MegaInt::operator--(int)
{
	MegaInt one{ "1" };
	MegaInt tmp{ *this };
	*this -= one;
	return tmp;
}

// normalize() : remove the leading '0'
void MegaInt::normalize(MegaInt& mi)
{
	deque<char>::iterator it = mi.mega_int.begin();

	while (it != mi.mega_int.end() && mi.mega_int.size() > 1 ){
		if (*it++ == '0'){
			mi.mega_int.pop_front();
		}
		else{
			break;
		}
	}
}

MegaInt MegaInt::add( const MegaInt& m1, const MegaInt& m2)
{
	MegaInt result;
	if (m1.mega_sign == m2.mega_sign){
		result = plus(m1, m2);
		result.mega_sign = m1.mega_sign;

	}
	else {
		if (m1 > m2){
			result = minus(m1, m2);
			result.mega_sign = m1.mega_sign;
		}
		else if (m1 < m2){
			result = minus(m2, m1);
			result.mega_sign = m2.mega_sign;

		}
		else {
			result = MegaInt{ "0" };
			result.mega_sign = false;
		}

	}

	normalize(result);      // normalize
	return result;

}

MegaInt MegaInt::subtract(const MegaInt& m1, const MegaInt& m2)
{
	MegaInt result;
	if (m1.mega_sign != m2.mega_sign){
		result = plus(m1, m2);
		result.mega_sign = m1.mega_sign;
	}
	else{
		if (m1 > m2){
			result = minus(m1, m2);
			result.mega_sign = m1.mega_sign;
		}
		else if (m1 < m2){
			result = minus(m2, m1);
			result.mega_sign = !(m1.mega_sign);
		}
		else {
			result = MegaInt{ "0" };
			result.mega_sign = false;
		}
	}

	normalize(result);

	return result;
}


MegaInt MegaInt::plus(const MegaInt& m1, const MegaInt& m2)
{
	MegaInt result;
	int carry = 0;
	int j = m1.mega_int.size() - 1;
	int k = m2.mega_int.size() - 1;
	int i = (j > k ? j : k);
	int tmp;

	while (j >= 0 && k >= 0) {
		tmp = m1[j] + m2[k] + carry;
		result.mega_int.push_front(static_cast<char>((tmp % 10) + '0'));
		carry = tmp / 10;
		i--;
		j--;
		k--;
	}

	while (j >= 0) {
		tmp = m1[j] + carry;
		result.mega_int.push_front(static_cast<char>((tmp % 10) + '0'));
		carry = tmp / 10;
		i--;
		j--;
	}

	while (k >= 0) {
		tmp = m2[k] + carry;
		result.mega_int.push_front(static_cast<char>((tmp % 10) + '0'));
		carry = tmp / 10;
		i--;
		k--;
	}

	result.mega_int.push_front(static_cast<char>(carry + '0'));

	return result;

}


MegaInt MegaInt::minus(const MegaInt& m1, const MegaInt& m2)
{
	MegaInt result;
	int borrow = 0;
	int j = m1.mega_int.size() - 1;
	int k = m2.mega_int.size() - 1;
	int i = (j > k ? j : k);
	int tmp = 0;

	while (j >= 0 && k >= 0) {
		tmp = m1[j] - (m2[k] + borrow);
		borrow = 0;
		if (tmp < 0){
			borrow = 1;
			tmp += 10;
		}
		result.mega_int.push_front(static_cast<char>((tmp % 10) + '0'));
		i--;
		j--;
		k--;
	}

	while (j >= 0){
		tmp = m1[j] - borrow;
		borrow = 0;
		if (tmp < 0){
			borrow = 1;
			tmp += 10;
		}
		result.mega_int.push_front(static_cast<char>((tmp % 10) + '0'));
		i--;
		j--;
	}

	if (borrow == 1 || k >= 0){
		throw "X cannot be less then Y in (X-Y)";
	}
	else{
		return result;
	}
}

MegaInt MegaInt::subMultiply(const MegaInt& m, int i, int& carry)
{
	MegaInt result, zero{ "0" };

	if (i == 0){	return zero;	}
	
	int j = m.mega_int.size() - 1;
	int tmp = 0;

	while (j >= 0){
		tmp = (m[j] * i) + carry;
		result.mega_int.push_front(static_cast<char>((tmp % 10) + '0'));
		carry = tmp / 10;
		j--;
	}

	// last carry
	result.mega_int.push_front(static_cast<char>(carry + '0'));
	normalize(result);
	return result;
}

MegaInt MegaInt::multiply(const MegaInt& m1, const MegaInt& m2)
{
	MegaInt result{ "0" }, tmpRes;

	const MegaInt* p1;	//large
	const MegaInt* p2;
	int carry = 0;

	// choose large one = p1
	if (m1 > m2){
		p1 = &m1;
		p2 = &m2;
	}
	else {
		p1 = &m2;
		p2 = &m1;
	}

	int j = p2->mega_int.size() - 1;
	unsigned long int sup = 0;

	while (j >= 0){
		tmpRes = subMultiply(*p1, (*p2)[j], carry);
		for (unsigned long int l_k = 0; l_k < sup; l_k++){
			tmpRes.mega_int.push_back('0');
		}
		result += tmpRes;
		j--;
		sup++;
		carry = 0;
	}

	normalize(result);
	if (m1.mega_sign != m2.mega_sign){
		result.mega_sign = true;
	}else {
		result.mega_sign = false;
	}
	return result;
}

MegaInt MegaInt::divide(MegaInt m1, MegaInt m2, int mode)
{
	MegaInt m_dividend, m_quotient, m_remainder, m_zero{ "0" }, m_guess{ "5" };
	bool t_signed;

	string s_fcs_dividend{ "" };
	int sz_2 = m2.mega_int.size();

	deque<char>::const_iterator it = m1.mega_int.begin();
	
	int ii = 0;

	if (m1.mega_sign != m2.mega_sign) {
		t_signed = true;
	}
	else {
		t_signed = false;
	}
	m1.mega_sign = false;
	m2.mega_sign = false;



	while (it != m1.mega_int.end()){
		// get initial divident
		s_fcs_dividend.append(1, *it++);
		ii++;
		if (ii < sz_2){
			continue;
		}
		
		m_dividend = s_fcs_dividend;
		
		// get divide
		if ( m2 > m_dividend) {
			m_guess = m_zero;
			m_remainder = m_dividend;
		}
		else {

			while (true){
				m_remainder = m_guess * m2 - m_dividend;	// m_guess starts from '5'
				MegaInt nextMega = m_remainder + m2;

				if (m_remainder > m_zero && m_remainder.mega_sign == false ){
					m_guess--;
				}
				else if ((nextMega > m_zero && nextMega.mega_sign == true) || nextMega == m_zero ){
					m_guess++;
				}
				else {
					break;
				}
			}
			
		}

		m_quotient.mega_int.push_back( m_guess.mega_int.at(0) );

		megaInt2string(m_remainder, s_fcs_dividend);
		m_guess = string("5");
	}

	if (mode == 1){			// '/'
		normalize(m_quotient);
		m_quotient.mega_sign = t_signed;
		return m_quotient;
	}else{					// '%'
		normalize(m_remainder);
		m_remainder.mega_sign = false;
		return m_remainder;
	}

}

void MegaInt::megaInt2string(const MegaInt& m, string& str)
{
	str.clear();

	if (m.mega_int.size() == 1 && m.mega_int.at(0) == '0'){
		return;
	}

	deque<char>::const_iterator it = m.mega_int.begin();

	while (it != m.mega_int.end()) {
		str.append(1, *it++);
	}
}
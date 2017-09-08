//
// Created by kcmmac on 2017-06-26.
//

#include "MegaCalc.h"

using namespace std;


MegaCalc::MegaCalc() : valAcc("0") {}

void MegaCalc::run()
{
    cout << "Welcome to MegaCalculator" << endl;
    cout << "=========================" << endl;

    string inStr;
    char inCh = '\0';
	MegaInt tmp0{ "0" };

    do {
        cout << endl << "Accumulator: " << valAcc << endl;
        cout << "Enter input: " ;

        getline(cin, inStr);

		if (inStr.length() < 1){
			cout << "Wrong input, try again" << endl;
			continue;
		}
		
		// remove white spaces
		removeWS(inStr);
		removeTabs(inStr);

        MegaInt inputMegaInt;
        inCh = inStr.at(0);

        if( inStr.length() > 1){
            string newStr = inStr.substr(1,inStr.length());
			string nosign_str;
			// input validation e.g. '+=12'
			// error if not the rest is digit.

			char char_sign = newStr.at(0);
			if (char_sign == '+' || char_sign == '-'){
				nosign_str = newStr.substr(1, newStr.length());
			}
			else{
				nosign_str = newStr;
			}


			if (!is_digit(nosign_str)){
				cout << "Wrong input: " << inStr << " try again. " << endl;
				continue;
			}

			inputMegaInt = newStr;
		
        }

        MegaInt result;

        switch(inCh){
            case '+':
				valAcc = valAcc + inputMegaInt;
                break;
            case '-':
				valAcc = valAcc - inputMegaInt;
                break;
			case '*':
				valAcc = valAcc * inputMegaInt;
				break;
			case '/':
				valAcc = valAcc / inputMegaInt;
				break;
			case '%':
				valAcc = valAcc % inputMegaInt;
				break;
			case '=':
				valAcc = inputMegaInt;
				break;
			case 'c':
				valAcc = tmp0;
				break;
			case 'n':
				valAcc.mega_sign == true ? valAcc.mega_sign = false : valAcc.mega_sign = true;
				break;
			case 'f':
				factorial(valAcc);
				break;
			case 'h':
				hailstone(valAcc);
				break;
            case 'q':
                break;
            default:
                cout << "Wrong input, try again" << endl;

        }


    } while( inCh != 'q' );

}

void MegaCalc::hailstone(MegaInt mi)
{
	const MegaInt m_one{ "1" };
	const MegaInt m_two{ "2" };
	MegaInt m_three{ "3" };
	MegaInt m{ mi };
	m.mega_sign = false;	//ignore negative

	cout << "> " << m << endl;

	MegaInt m_seq{ "1" };
	while (true) {
		if (m == m_one){
			break;
		}

		if (m % m_two == m_one) {	//odd
			m = (m_three * m) + m_one;
		}else {	//even
			m = m / m_two;
		}
		cout << "> " << m << endl;
		m_seq++;
	}
	
	cout << endl << "length of the hailstone(" << mi << ") sequence: " << m_seq << endl;;
}

MegaInt MegaCalc::factorial(const MegaInt& m)
{
	const MegaInt one{ "1" };
	MegaInt mega_fact{ one };

	for(MegaInt mega_k = one; mega_k <= m; ++mega_k){
	    mega_fact *= mega_k;
	    cout << mega_k << "!= " << mega_fact << endl;
	}

	return mega_fact;
}

void MegaCalc::removeWS(string& str)
{
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
}

void MegaCalc::removeTabs(string& str)
{
	str.erase(remove(str.begin(), str.end(), '\t'), str.end());
}

bool MegaCalc::is_digit(string& str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit);
}
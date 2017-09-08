#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <map>
#include <locale>
#include <iterator>
#include <iomanip>
#include <functional>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include "MyCompare.h"

using namespace std;

bool is_palinedrome(const string &phrase);
void test_is_palinedrome();
void test_second_max();

template < class Iterator >
std::pair<Iterator, bool> second_max(Iterator start, Iterator finish);

void print_word_frequency_1(const string &filename);
void print_word_frequency_2(const string &filename);
void print_word_index(const string &filename);

string remove_leading_trailing_non_alpha(const string& word);


int main() {

    test_is_palinedrome();
    cout << "--------------------------------------------------" << endl;

    test_second_max();
    cout << "--------------------------------------------------" << endl;

    string filename = "input.txt";
    print_word_frequency_1(filename);
	cout << "--------------------------------------------------" << endl;

    print_word_frequency_2(filename);
	cout << "--------------------------------------------------" << endl;

    print_word_index(filename);

    return 0;
}



void test_is_palinedrome(){
    string str_i = string("Was it a car or a cat I saw?");
    string str_u = string("Was it a car or a cat U saw?");

    cout << "the phrase \"" + str_i + "\" is " + (is_palinedrome(str_i) ? "":"not ") + "a palinedrome\n";
    cout << "the phrase \"" + str_u + "\" is " + (is_palinedrome(str_u) ? "":"not ") + "a palinedrome\n";
}


// is_palinedrome() : test if the given string is palinedrome using STL algorithm 
bool is_palinedrome(const string &phrase){

    string temp;
    std::remove_copy_if(phrase.begin(), phrase.end(), std::back_inserter(temp) , [] (string::value_type val) { return !( isalpha(val) ); } );
    std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper );

    return std::equal(temp.begin(), temp.begin()+temp.size() / 2 , temp.rbegin());

}


void test_second_max(){
    vector<int> int_vec{1,1,5,5,7,7};

    auto retval = second_max( int_vec.begin(), int_vec.end());

    if(retval.second){
        cout << "The second largest element in int_vec is " << *retval.first << endl;
    } else{
        if( retval.first == int_vec.end() ) {
            cout << "List empty, no element" << endl;
        }else {
            cout << "Container's elements are all equal to " << *retval.first << endl;

        }
    }

}


// second_max(): function template that finds the seocnd largest number from the given range.
template < class Iterator >
std::pair<Iterator, bool> second_max(Iterator start, Iterator finish){

    Iterator iter_1st, iter_2nd;
    bool is_compared = false;

    if( start == finish ){      //empty
        return std::make_pair(finish, false);
    }else {
		//suppose the largest one is first iterator, and 2nd largest is second iterator.
        iter_1st=start;
        iter_2nd=start+1;

        for(Iterator it=start+1; it!= finish; ++it){
            if( *it > *iter_1st) {
                iter_2nd = iter_1st;
                iter_1st = it;
                is_compared = true;
            } else{
                if( *it > *iter_2nd){
                    iter_2nd = it;
                    is_compared = true;
                }
            }
        }

        if(is_compared){
            return std::make_pair(iter_2nd, true);
        }else{
            return std::make_pair(start, false);
        }

    }

};


void print_word_frequency_1(const string &filename) {

    std::ifstream ifs = std::ifstream(filename);
	if (!ifs){
		cout << "No such file found " << endl;
		//throw std::invalid_argument(string("could not open file") + filename);
		exit(0);
	}

    std::map<string, int> word_frequency_map;

    string line;

    while(getline(ifs, line)){

        istringstream iss(line);

        string word;
        while( iss >> word ){
            ++word_frequency_map[remove_leading_trailing_non_alpha(word)];
        }
    }

    for(const auto &word : word_frequency_map){
        cout << setw(10) << word.first << " " << word.second << endl;
    }

};


void print_word_frequency_2(const string &filename) {

    std::ifstream ifs = std::ifstream(filename);
	if (!ifs){
		cout << "No such file found " << endl;
		exit(0);
	}
	

    std::map<string,int, MyCompare> word_frequency_map;

    string line;

    while(getline(ifs, line)){

        istringstream iss(line);

        string word;
        while( iss >> word ){
            ++word_frequency_map[remove_leading_trailing_non_alpha(word)];
        }
    }

    for(const auto &word : word_frequency_map){
        cout << setw(10) << word.first << " " << word.second << endl;
    }

};


bool is_alphabet(string::value_type ch){
    cout << ch << ":" << isalpha( ch ) << endl;
    return !isalpha( ch );
}


string remove_leading_trailing_non_alpha(const string& word){
    string temp{word};

    // --- remove leading part
    for(size_t k = 0; k < temp.size(); k=0){
        if(!isalpha( temp.at(k) ) ){
            temp.erase(k,1);
        }else{
            break;
        }
    }

    // --- remove trailing part
    for(size_t j = temp.size(); j > 0; j = temp.size() ){
        if(!isalpha( temp.at(j-1) )){
            temp.erase(j-1,1);
        }else{
            break;
        }
    }

    return temp;
}


void print_word_index(const string &filename){

    std::ifstream ifs = std::ifstream(filename);
	if (!ifs){
		cout << "No such file found " << endl;
		exit(0);
	}


//    std::map<string, int> word_frequency_map;
    std::map<string,set<int>, MyCompare> word_frequency_map;

    string line;
    int line_num = 1;

	while(getline(ifs, line)){

        istringstream iss(line);
        string word;

        while( iss >> word ){
            string t_word = remove_leading_trailing_non_alpha(word);

            set<int> s = word_frequency_map[t_word];
            s.insert(line_num);
            word_frequency_map[t_word] = s;
        }
        line_num++;
    }

	// print 
    for(const auto &word : word_frequency_map){
        cout << setw(10) << word.first << " ";
        for( int i : word.second ){
            cout << i << " ";
        }
        cout << endl;
    }
}
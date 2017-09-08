//
// Created by kcmmac on 2017-07-12.
//

#include <vector>
#include "Rhombus.h"

Rhombus::Rhombus(int diagonal, const string& dn) : Shape("Rhombus", dn) {
    if( diagonal % 2 == 0){
        diagonal++;
    }
    this->diagonal = diagonal;
}

Rhombus::~Rhombus() {
}

vector<vector<char>> Rhombus::draw(char penChar, char fillChar) const {
    vector<vector<char>> rect;


    size_t pos_left = this->diagonal / 2 + 1;
	size_t pos_right = this->diagonal / 2 + 1;

    bool reverse = false;

    rect.resize( this->diagonal );

	for (size_t k = 0; k < rect.size(); k++){
        rect[k].resize( this->diagonal );
		for (size_t j = 0; j < rect[k].size(); j++){
            if( j  >= pos_left-1 && j <= pos_right-1 ){
                rect[k][j] = penChar;
            }else {
                rect[k][j] = fillChar;
            }
        }

        if( reverse ){
            pos_left++;
            pos_right--;
        }else{
            pos_left--;
            pos_right++;
        }

        if(pos_left == 1){
            reverse = true;
        }

    }

    return rect;

}

void Rhombus::scale(int i) {
    if( this->diagonal + 2*i >= 1 ){
        this->diagonal += 2*i;
    }
}



int Rhombus::bounding_box_height() const {
    return this->diagonal;
}

int Rhombus::bounding_box_width() const {
    return this->diagonal;
}


int Rhombus::scr_area() const {
    int n = this->diagonal / 2;
    return 2 * n * (n + 1) + 1;
}

double Rhombus::geo_area() const {
	double t1 = this->diagonal * this->diagonal;
    return t1 / 2;
}

int Rhombus::scr_perimeter() const {
    return 2 * (this->diagonal - 1);
}

double Rhombus::geo_perimeter() const {
    return 2 * sqrt(2) * this->diagonal;
}
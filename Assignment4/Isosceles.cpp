//
// Created by kcmmac on 2017-07-12.
//

#include "Isosceles.h"

// ctor, call the base ctor
Isosceles::Isosceles(int b, const string& dn) : Triangle(b%2 ==0? b+1: b,  b%2==0? (b+2)/2 : (b+1)/2 , "Isosceles", dn) { }

Isosceles::~Isosceles() { }

// assign values to 2d vectors
vector<vector<char>> Isosceles::draw(char penChar, char fillChar) const {
    vector<vector<char>> rect;

    size_t pos_left = this->base / 2 + 1;
	size_t pos_right = pos_left;

    rect.resize(this->height);

    for(size_t j=0; j < rect.size() ; j++){

        rect[j].resize(this->base );
		for (size_t k = 0; k < rect[j].size(); k++){

            if( k >= pos_left-1 && k <= pos_right-1 ){
                rect[j][k] = penChar;
            } else{
                rect[j][k] = fillChar;
            }
        }

        pos_left--;
        pos_right++;

    }

    return rect;

}

// scale up or down of the shape size
void Isosceles::scale(int i) {
    if(this->base + 2*i >= 1){
        this->base += 2*i;
        this->height = (this->base + 1) / 2;
    }
}


int Isosceles::bounding_box_height() const {
    return this->height;
}

int Isosceles::bounding_box_width() const {
    return this->base;
}


int Isosceles::scr_area() const {
    return this->height * this->height;
}

double Isosceles::geo_area() const {
	double t1 = this->base * this->height;
    return t1 / 2;
}

int Isosceles::scr_perimeter() const {
    return 4 * (this->height-1) ;
}

double Isosceles::geo_perimeter() const {
    return this->base + 2 * sqrt( 0.25 * pow(this->base,2) + pow(this->height, 2) );
}



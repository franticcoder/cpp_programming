//
// Created by kcmmac on 2017-07-12.
//

#include "RightTriangle.h"

RightTriangle::RightTriangle(int b, const string& dn) : Triangle(b , b, "RightTriangle", dn) { }

RightTriangle::~RightTriangle() {

}

vector<vector<char>> RightTriangle::draw(char penChar, char fillChar) const {
    vector<vector<char>> rect;


    size_t cnt = 0;

    rect.resize( this->height );

    for(size_t j=0; j < rect.size() ; j++){

        rect[j].resize( this->base );
		for (size_t k = 0; k < rect[j].size(); k++){
            if( k <= cnt ){
                rect[j][k] = penChar;
            } else{
                rect[j][k] = fillChar;
            }
        }
        cnt++;
    }

    return rect;

}

void RightTriangle::scale(int i) {
    if( this->base + i >= 1 ){
        this->base += i;
        this->height += i;
    }

}

int RightTriangle::bounding_box_height() const {
    return this->height;
}

int RightTriangle::bounding_box_width() const {
    return this->base;
}


int RightTriangle::scr_area() const {
    return this->height * (this->height + 1) / 2;
}

double RightTriangle::geo_area() const {
    double tmp = this->base * this->height / 2;
    return tmp;
}

int RightTriangle::scr_perimeter() const {
    return 3 * (this->height-1) ;
}

double RightTriangle::geo_perimeter() const {
    return (2  + sqrt(2)) * this->height;
}

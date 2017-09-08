//
// Created by kcmmac on 2017-07-11.
//

#include "Rectangle.h"

using namespace std;


Rectangle::Rectangle(int _w, int _h, const string& dn ) : width(_w), height(_h), Shape("Rectangle", dn ) { }

Rectangle::~Rectangle() { }


vector<vector<char>> Rectangle::draw(char penChar, char fillChar) const {
    vector<vector<char>> rect;

    rect.resize( this->height );

	for (size_t j = 0; j < rect.size(); j++){

        rect[j].resize(this->width);

		for (size_t k = 0; k < rect[j].size(); k++){
            rect[j][k] = penChar;
        }
    }

    return rect;
}


void Rectangle::scale(int i) {
    // check range
    if( this->width + i >= 1 && this->height + i >= 1){
        this->width += i;
        this->height += i;
    }
}


int Rectangle::bounding_box_height() const {
    return this->height;
}

int Rectangle::bounding_box_width() const {
    return this->width;
}


int Rectangle::scr_area() const {
    return (this->width * this->height);
}

double Rectangle::geo_area() const {
    double tmp = this->width * this->height;
    return tmp;
}

int Rectangle::scr_perimeter() const {
    return 2 * (this->width + this->height) - 4;
}

double Rectangle::geo_perimeter() const {
    return 2 * (this->width + this->height);
}

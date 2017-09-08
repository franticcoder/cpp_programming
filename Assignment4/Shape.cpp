//
// Created by kcmmac on 2017-07-11.
//

#include "Shape.h"

int Shape::next_id = 1;		// initialize to 1

Shape::Shape(const string& gname, const string& dname) : generic_name(gname), descriptive_name(dname) {
    this->idnum = next_id++;
}

Shape::~Shape() {}

int Shape::getIdnum() const {
    return idnum;
}

// toString() : display information of the shape.
string Shape::toString() const {
	ostringstream sout;
	sout << "Shape Information\n";
	sout << "-----------------\n";
	sout << setw(16) << left << "Static type:" << typeid(this).name() << endl;
	sout << setw(16) << "Dynamic type:" << typeid(*this).name() << endl;
	sout << setw(16) << "Generic name:" << generic_name << endl;
	sout << setw(16) << "Description:" << descriptive_name << endl;
	sout << setw(16) << "id:" << idnum << endl;
	sout << setw(16) << "B. box width:" << this->bounding_box_width() << endl;
	sout << setw(16) << "B. box geight:" << this->bounding_box_height() << endl;
	sout << setw(16) << "Scr area:" << this->scr_area() << endl;
	sout << setw(16) << setprecision(2) << fixed << "Geo area:" << this->geo_area() << endl;
	sout << setw(16) << "Scr perimeter:" << this->scr_perimeter() << endl;
	sout << setw(16) << "Geo perimeter:" << this->geo_perimeter() << endl;

	return sout.str();
}

// output the 2d vector to console
ostream& operator<<(ostream& sout, const vector<vector<char>> &grid) {
    for(vector<char> vec : grid){
        for(char ch : vec){
            sout << ch;
        }
        sout << endl;
    }

    return sout;
}

void Shape::draw_on_screen(char penChar, char fillChar) const {
    cout << this->draw(penChar, fillChar) << endl;
}


void Shape::write_image_to_screen(ostream& out, char penChar) {
    out << this->draw(penChar,' ') << endl;
}

void Shape::write_image_to_screen(ostream& out, char penChar, char fillChar) {
    out << this->draw(penChar,fillChar) << endl;
}


ostream& operator<<(ostream& sout, const Shape& spe){
    sout << spe.toString() << endl;
    return sout;
}


const string &Shape::getGeneric_name() const {
    return generic_name;
}

const string &Shape::getDescriptive_name() const {
    return descriptive_name;
}

void Shape::setDescriptive_name(const string &descriptive_name) {
    Shape::descriptive_name = descriptive_name;
}

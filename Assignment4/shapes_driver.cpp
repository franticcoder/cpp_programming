#include <iostream>
#include "Shape.h"
#include "Rectangle.h"
#include "Rhombus.h"
#include "RightTriangle.h"
#include "Isosceles.h"
#include "SlotMachine.h"

int main() {

	/*====================================
	  = Code for testing shapes			 =
	  ==================================== */
	/*
	Rectangle shape1(10,3);
	cout << shape1 << endl;

    Rhombus ace(16,"Ace of diamond");
	cout << ace.toString() << endl;
	ace.draw_on_screen(' ', 'o');
	ace.scale(-4);
	ace.write_image_to_screen(cout, '1');

	ace.scale(2);
	ace.write_image_to_screen(cout, 'A', '.');

	Isosceles iso(17);
	cout << iso.draw('\\','.') << endl;

	RightTriangle rt(10, "Carpenter's square");
	cout << rt << endl;
	*/
	

	/*====================================
	  = Code for starting the SlotMachine=
	  ==================================== */

	
    SlotMachine slot_machine;
    slot_machine.run();

    return 0;
	
}



//
// Created by kcmmac on 2017-06-02.
//


#include <iostream>
#include <string>
#include <fstream>
#include "Led.h"

using namespace std;

int main(int argc, char* argv[])
{

    string filename;

    switch(argc)
    {
        case 1:
            break;
        case 2:
			//get a filename to edit from the command
            filename = argv[1];
            break;
        default:
            cout << ("Too many arguments - all discarded") << endl;
    }

    Led led(filename);
    led.run();


    return 0;
}
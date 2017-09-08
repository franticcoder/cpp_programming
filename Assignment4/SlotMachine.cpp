//
// Created by kcmmac on 2017-07-13.
//

#include "SlotMachine.h"


SlotMachine::~SlotMachine() { }

void SlotMachine::run() {
    this->token = 10;
	srand(unsigned(time(0)));

    display_intro();

    while(true){
        cout << "How much would like to bet ( enter 0 to quit )? ";
        cin >> bet_token;

        if(cin.fail()){
            cout << "Only integer is accepted. Try again." << endl;
			cin.clear();
			cin.ignore(100,'\n');
            continue;
        }
        if( bet_token > this->token ){
            cout << "Cannot bet more than your tokens. Please re-bet" << endl;
            continue;
        }
		if (bet_token < 0) {
			cout << "The bet must be at least 1. Please re-bet" << endl;
			continue;
		}

        if( bet_token == 0){
            break;
        }

        make_shapes();
        display_shapes();

        report_status();

        release_shapes();

        if( token == 0){
            break;
        }
    }

    cout << "Game Over. You now have " << token << " token(s)." << endl;

}

void SlotMachine::display_intro() {
    cout << "Welcome to this 3-Reel Slot Machine Game!" << endl;
    cout << "Each reel will randomly display one of four shapes, each in 25 sizes." << endl;
    cout << "To win 3 times your bet, you need 3 similar shapes of the the same size." << endl;
    cout << "To win 2 times your bet, you need 3 similar shapes." << endl;
    cout << "To win or lose nothing, you need 2 similar shapes." << endl;
    cout << "Otherwise, you lose your bet." << endl;
    cout << "You start with " << this->token << " free tokens!" << endl;

}

// get_rnd_num() : get a random number generated between the given min to max number.
int SlotMachine::get_rnd_num(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void SlotMachine::make_shapes() {
    for(size_t k=0; k < shape_reel.size(); k++){
        make_shape(k);
    }
}

void SlotMachine::make_shape(int r) {
    int r_type;
    int r_size;
    int r_height;
	
	// determine the shape and size using randome generation function.
    r_type = get_rnd_num(0,3);
    r_size = get_rnd_num(1,25);

//    cout << "r_type=" << r_type << " , r_size=" << r_size <<  endl;
    if(r_type == 0){
        shape_reel[r] = new Rhombus(r_size);
    }else if(r_type == 1){
        shape_reel[r] = new Isosceles(r_size);
    }else if(r_type == 2){
        shape_reel[r] = new RightTriangle(r_size);
    }else if(r_type == 3){
        r_height = get_rnd_num(1,25);
        shape_reel[r] = new Rectangle(r_size, r_height);
    }

}

// display_shapes() : display the randomly generated shapes to the console.
void SlotMachine::display_shapes() {

    size_t h1 = shape_reel[0]->bounding_box_height();
	size_t h2 = shape_reel[1]->bounding_box_height();
	size_t h3 = shape_reel[2]->bounding_box_height();
    size_t max_height = max(max(h1,h2), h3) + 2;

    size_t w1 = shape_reel[0]->bounding_box_width();
	size_t w2 = shape_reel[1]->bounding_box_width();
	size_t w3 = shape_reel[2]->bounding_box_width();

    vector<vector<char>> vec1 = shape_reel[0]->draw();
    vector<vector<char>> vec2 = shape_reel[1]->draw();
    vector<vector<char>> vec3 = shape_reel[2]->draw();


	for (size_t k = 0; k < max_height; k++){

        if(k == 0 || k == max_height-1){
            cout << "+-";
            for(size_t i1=0; i1 < w1; i1++){
                cout << "-";
            }
            cout << "-+-";
			for (size_t i2 = 0; i2 < w2; i2++){
                cout << "-";
            }
            cout << "-+-";
			for (size_t i3 = 0; i3 < w3; i3++){
                cout << "-";
            }
            cout << "-+";
        }else{
            cout << "| ";
            for(size_t i1=0; i1 < w1; i1++){
                if( k-1 >= vec1.size() ){
                    cout << ' ';
                }else {
                    cout << vec1[k - 1][i1];
                }
            }
            cout << " | ";
			for (size_t i2 = 0; i2 < w2; i2++){
                if( k-1 >= vec2.size() ){
                    cout << ' ';
                }else {
                    cout << vec2[k - 1][i2];
                }
            }
            cout << " | ";
			for (size_t i3 = 0; i3 < w3; i3++){
                if( k-1 >= vec3.size() ){
                    cout << ' ';
                }else {
                    cout << vec3[k - 1][i3];
                }
            }
            cout << " |";

        }
        cout << endl;

    }


    for(size_t k = 0; k < shape_reel.size(); k++ ){
        cout << "(" << shape_reel[k]->getGeneric_name() << ", " << shape_reel[k]->bounding_box_width() << ", " << shape_reel[k]->bounding_box_height() << ") ";
    }
    cout << endl;
}

// report_status(): report the result of a bet
void SlotMachine::report_status() {
    int shape_iden = 0 ;
    int size_iden = 0;
    string s1 = shape_reel[0]->getGeneric_name();
    string s2 = shape_reel[1]->getGeneric_name();
    string s3 = shape_reel[2]->getGeneric_name();

    int sz1 = shape_reel[0]->bounding_box_height();
    int sz2 = shape_reel[1]->bounding_box_height();
    int sz3 = shape_reel[2]->bounding_box_height();


    // shape
    if( s1.compare( s2 ) == 0){
        if( s1.compare( s3 ) == 0 ){
            shape_iden = 3;
        }else{
            shape_iden = 2;
        }
    }else {
        if( s1.compare( s3 ) == 0 ){
            shape_iden = 2;
        }else{
            if( s2.compare( s3 ) == 0){
                shape_iden = 2;
            }else{
                shape_iden = 0;
            }
        }
    }

    // size
    if( sz1 == sz2 ){
        if( sz1 == sz3 ){
            size_iden = 3;
        }else{
            size_iden = 2;
        }
    }else{
        if( sz1 == sz3 ){
            size_iden = 2;
        }else{
            if(sz2 == sz3){
                size_iden = 2;
            }else{
                size_iden = 0;
            }
        }

    }
    // deduct bet
    token -= bet_token;
	//    cout << "sh:" << shape_iden << ", sz:" << size_iden << endl;

    // result
    if( shape_iden == 3 && size_iden == 3){
        cout << "Congratulations! You win 3 times your bet: " << bet_token * 3 << endl;
        token += bet_token * 3;
    }else if( shape_iden == 3){
        cout << "Congratulations! You win 2 times your bet: " << bet_token * 2 << endl;
        token += bet_token * 2;
    }else if( shape_iden == 2){
        cout << "You don't win, you don't lose, you are safe!" << endl;
        token += bet_token;
    }else{
        cout << "You lose your bet" << endl;
    }
    cout << "You now have " << token << " tokens!" << endl ;

}

// release_shapes() : release the storage for the shapes after being used.
void SlotMachine::release_shapes() {
    for(size_t k = 0; k < shape_reel.size(); k++){
        delete shape_reel[k];
    }

}

//
// Created by kcmmac on 2017-06-02.
//

#include "Led.h"


using  namespace std;

Led::Led() : last_line{ 0 }, is_file_editted{ false }, current_line{0} { }

Led::Led(const string& filename)
{
    this->filename = filename;
    this->last_line = 0;
	this->current_line = 0;
    this->is_file_editted = false;

    // no name -> default.txt

    string in_line;
    int count = 0;

    //if a filename exists, read the file and save to buffer
    if ( filename.length() > 0 ) {

        ifstream fin(filename.c_str());			// open a file w/ filename

        if (!fin) {
            cout << "Unable to open file " << filename << endl;
            cout << "\"" << filename << "\" [New File]" << endl;

        } else {

            if (fin.is_open()) {
                while (getline(fin, in_line)) {
                    buffer.push_back(in_line);
                    ++count;
                }
            }

            current_line = count;
            last_line = count;

            cout << "\"" << filename << "\" " << count << ((count > 1) ? " lines" : " line") << endl;
        }

    } else {        //no filename
        cout << "\"?\" [New File]" << endl;

    }
}


void Led::run()
{

    string command_line;
    Command cmd;
    cout << "Entering command mode" << endl;

    do{
        cout << ":";

		// get command string from the console.
        getline(cin, command_line );

		// parsing the command.
        cmd.parse(command_line, current_line, last_line);

		// execute the command.
        execute(cmd);

    } while( cmd.getSymbol() != 'q' );

}



void Led::execute(Command & cmd)
{
    // if the command is invalid, show error message.
    if( !cmd.isCommand_valid() )
    {
        cout << cmd.getMsg() << endl;
        return;
    }

	// execute the command according to the comand type.
    switch(cmd.getSymbol())
    {
        case 'p': print( cmd.getStart_line(), cmd.getEnd_line(), 0 ); break;
        case 'a': append_line( cmd.getEnd_line() );    break;
        case 'i': append_line( cmd.getEnd_line() -1 );    break;   //insert
        case 'q': quit();          break;
        case 'w': writeToFile();    break;
        case '=': print_curline_addr(); break;
        case 'n': print( cmd.getStart_line(), cmd.getEnd_line(), 1 ); break;
        case 'r': remove_line( cmd.getStart_line(), cmd.getEnd_line()); break;
        case 'c': change_txt2txt( cmd.getStart_line(), cmd.getEnd_line() ); break;
        case 'u': move_up(cmd.getEnd_line()); break;
        case 'd': move_down(cmd.getEnd_line()); break;
        default :
            ;

    }


}

void Led::quit()
{
    if(is_file_editted){	// save when there is a edition to the file.

        string sin;

        while(true) {
            cout << "Save changes to " << "\"" << this->filename << "\" (y/n)?";

            getline(cin, sin);

            if (memcmp("y", sin.data(), sin.length()) == 0) {
                writeToFile();
                break;
            } else if(memcmp("n", sin.data(), sin.length()) == 0) {
                // no write
                break;
            } else {
                cout << "invalid answer: " << sin << endl;
                cout << "enter y for yes and n for no." << endl;
            }
        }
    }
    cout << "quitting led ... bye" << endl;
}

void Led::print_curline_addr()
{
    cout << current_line << endl;
}

// print() : print the strings from the given starting and ending line numbers.
void Led::print(int istart, int iend, int mode)
{
	if (last_line == 0) {
		cout << "There is no line to print" << endl;
		return;
	}
	
	if (!is_valid_range(istart, iend)) {
		return;
	}
    
    int cnt = istart;
	
    list<string>::iterator it = buffer.begin();			// using iterator
    advance(it, istart-1);
    int line_num = istart;

    do{
        if(mode == 1 ){
            cout << line_num << " ";
        }
        cout << *it << endl;
        current_line = cnt;
        cnt++;
        ++it;
        line_num++;
    }while( cnt <= iend );

}

// remove_line(): remove lines w/ starting and ending line numbers.
void Led::remove_line(int istart, int iend)
{
	if (last_line == 0) {
		cout << "There is no line to remove" << endl;
		return;
	}

	if (!is_valid_range(istart, iend)) {
		return;
	}

    list<string>::iterator it = buffer.begin();
    advance(it, istart-1);
    int cnt = istart;

    do{
        it = buffer.erase( it );
        //it++;				// no need to ++, bcuz erase() change the order.
        cnt++;
        is_file_editted = true;
    } while( cnt <= iend );

    int sz = buffer.size();

    if( last_line == iend ){
        current_line = istart - 1;
    } else{
        current_line = istart;
    }

    last_line = sz;

}

// append_line() : append a line or lines to the given position.
void Led::append_line(int pos)
{
    // validate pos range.
    if( pos < -1 || pos > last_line ){
		cout << "Out of range: 1 to " << last_line << endl;
		return;
	}
	else if (pos == -1){
		pos = 0;
	}

    string input_line;
    list<string>::iterator it = buffer.begin();
    advance(it, pos);
    int cnt = pos;

    while( true )
    {
        getline(cin, input_line);

        if( input_line.length() != 0 &&
            memcmp(".", input_line.data(), input_line.length()) == 0 ){ break; }

        buffer.insert(it, input_line);
        cnt++;
        last_line++;
        is_file_editted = true;
        current_line = cnt;
    }


}

// change_txt2txt() : change a word to the one given within the given range.
void Led::change_txt2txt(int istart, int iend)
{
	if (!is_valid_range(istart, iend)) {
		return;
	}

	// find str and change to strto
    string str_from, str_to;
    cout << "change what ? ";
    getline(cin, str_from);

    cout << endl << "to what ? ";
    getline(cin, str_to);

    // replace
    list<string>::iterator it = buffer.begin();
    advance(it, istart-1);
    int cnt = istart;
    string str;

    // change to replace the second occurrence (added)
    size_t iPos = 0;

    do{
        str = *it;

        //size_t iPos = str.find(str_from);
        while(true)
        {
            iPos = str.find(str_from, iPos+1);

            if (iPos != string::npos) {
                str.replace(iPos, str_from.size(), str_to);
                *it = str;
                is_file_editted = true;
            }else{
                break;
            }
        }

        current_line = cnt;
        it++;
        cnt++;
        iPos = 0;

    } while ( cnt <= iend );


}


void Led::move_up(int offset)
{
    if(!is_line_exist()){
        return;
    }

    if( current_line - offset >= 0 )
    {
        current_line -= offset;
    }else
    {
        cout << "BOF reached " << endl;
        current_line = 1;
    }

    print_n_line(current_line);

}


void Led::move_down(int offset)
{
    if(!is_line_exist()){
        return;
    }

    if( current_line + offset > last_line)
    {
        cout << "EOF reached" << endl;
        current_line = last_line;

    }else
    {
        current_line += offset;
    }

    print_n_line(current_line);

}


bool Led::is_valid_range(int is, int ie)
{
	if (is < 0 || ie > last_line){
		cout << "Out of range for line address : 1 to " << last_line << endl;
		return false;
	}
	else {
		return true;
	}
}

bool Led::is_line_exist()
{
    if( current_line == 0)
    {
        cout << "There is no content for this file. Please input something." << endl;
        return false;
    } else
    {
        return true;
    }

}

void Led::print_n_line(int line_num)
{
    list<string>::iterator it = buffer.begin();
    advance(it, line_num-1);
    cout << *it << endl;
}

void Led::writeToFile()
{
    // if there is no filename, get one.
    if(this->filename.length() < 1){
        string filenm;
        cout << "There is no filename. Enter a filename: " ;
        getline(cin, filenm);
        this->filename = filenm;

        if( cin.fail() ){
            cout << "FileName input Error" << endl;
            cin.clear();
            return;
        }
    }

    if( !is_file_editted )
    {
        return; //no need to save to file. no change.
    }

    ofstream fout(filename.c_str());
    if(!fout)
    {
        cout << "Cannot open the file for writing: " << filename << endl;
        return;
    }

    int lnum = 0;
    for( list<string>::iterator it = buffer.begin(); it != buffer.end(); it++ )
    {
        fout << *it << endl;
        lnum++;
    }

    is_file_editted = false;

    cout << "\"" << this->filename << "\" " << lnum << " line(s) written" << endl;

}
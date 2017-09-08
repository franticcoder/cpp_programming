//
// Created by Chungmin Kim on 2017-05-18.
//


#include "Menu.h"


//default constructor
Menu::Menu() {
	//initialize member variables
    option_list = new Text[1];
    max_list_size = 1;
    count = 0;
}

//copy constructor
Menu::Menu(const Menu & menu)
{
	//copy variables
    count = menu.count;
    max_list_size = menu.max_list_size;

    top_prompt = menu.top_prompt;
    bottom_prompt = menu.bottom_prompt;
    top_text = menu.top_text;
    bottom_text = menu.bottom_text;

	//allocate storage
    option_list = new Text[menu.max_list_size];

	//copy Text
    for(int k=0; k < menu.count; k++ )
    {
        option_list[k] = menu.option_list[k];
    }

}

//destructor
Menu::~Menu() {
	//deallocate storage
    delete [] option_list;
}


// double the capacity(storage) of the string dynamically
void Menu::double_capacity()
{
    int new_cap = 2 * max_list_size;

    Text *tmp = new Text[new_cap];

    for(int k=0; k < count ; k++)
    {
        tmp[k] = option_list[k];
    }

    delete [] option_list;
    option_list = tmp;
    max_list_size = new_cap;

}

// overloading operator=
Menu& Menu::operator=(const Menu & menu)
{
    if(this==&menu){ return *this; }

    delete [] option_list;

	//copy variables
    count = menu.count;
    max_list_size = menu.max_list_size;

    top_prompt = menu.top_prompt;
    bottom_prompt = menu.bottom_prompt;
    top_text = menu.top_text;
    bottom_text = menu.bottom_text;

    option_list = new Text[menu.max_list_size];

	// copy option_list from the rhs to the lhs.
    for(int k=0; k < menu.count; k++ )
    {
        option_list[k] = menu.option_list[k];
    }

    return *this;

}

// overloading operator<< 
ostream& operator<<(ostream & out, const Menu & m)
{
	int in_num, choice;

    while(true)
    {
        if( !(m.top_text.isEmpty()) ) { cout << m.top_text << endl; }

        if( !(m.top_prompt.isEmpty())){ cout << m.top_prompt << endl; }

		//display menus
        cout << m.toString() ;

        if( !(m.bottom_text.isEmpty())) { cout << m.bottom_text << endl; }

		// display "?->"
        cout << m.literal;

        if( !(m.bottom_prompt.isEmpty())  ) { cout << m.bottom_prompt; }

        cin >> in_num;

		//validate input, in a case that characters are inputed. 
		if (cin.fail())
		{
			cout << "Please enter an integer number, not character(s) and floating point numbers " << endl;
			cin.clear();
			cin.ignore(80, '\n');
			continue;
		}

        if( m.count > 0)
        {
            if (in_num >= 1 && in_num <= m.count)
            {
                choice = in_num;
                break;
            } else
			{
                cout << "Invalid choice " << in_num << ". It must be in the range [1," << m.count << "]" << endl;
            }
        }else
		{
            choice = in_num;
            break;
        }

    }

    cout << "you entered: " << choice << endl;
    return out;

}

// insert a Text object to the Menu with an index
void Menu::insert(int index, const Text & option)
{
    //validate index number ( 0 ~ count)
	if (index < 0 || index > count)
	{
		cout << "insertion failed, invalid index number!" << endl;
		return;
	}

	//double the capacity when the current storage is full
    if( capacity() == count )
    {
        double_capacity();
    }

    Text *tmpText = new Text[max_list_size];

	//copy the previous Text to the new storage
    for(int i=0; i < index; i++)
    {
        tmpText[i] = option_list[i];
    }

    tmpText[index] = option;

    for(int j=index+1; j < count+1 ; j++)
    {
        tmpText[j] = option_list[j-1];
    }

    delete [] option_list;
    option_list = tmpText;
    count++;

}

//insert a string(char*) to the last
void Menu::push_back(char * pOption)
{
    Text t = Text(pOption);
    insert(count, t );
}

//insert a string(Text&) to the last
void Menu::push_back(const Text & option)
{
    Text t = option;
    insert(count, t );
}

// remove a Text at the index position
Text Menu::remove(int index)
{
	//when there is no menu, do nothing and return empty Text
    if(count == 0) { return Text(""); }

    Text t = option_list[index];

    for(int k=index; k < count; k++)
    {
        option_list[k] = option_list[k+1];
    }
    count--;

    return t;
}

// return the number of Text arrays
int Menu::size()
{
    return count;
}

// return the current maximum number of storage
int Menu::capacity()
{
    return max_list_size;
}

// remove the last menu from the array
void Menu::pop_back()
{
    if( count >= 1)
    {
        remove(count-1);
    }

}

//return the Text object at index 'k'
Text Menu::get(int k)
{
	//validate index number ( 0 ~ count)
	if (k < 0 || k > count)
	{
		cout << "insertion failed, invalid index number!" << endl;
		return Text("");
	}
    
    return option_list[k];
}



// traverse the Text array and covert each text to a Text object.
Text Menu::toString() const
{
    Text tmpText("");

    if( count != 0 )
    {
        tmpText.append("\n");
        for(int k=0 ; k < count; k++)
        {
            tmpText.append("(");
			string str = to_string(k + 1);
            tmpText.append( str.c_str() );
            tmpText.append(") ");
            tmpText.append(option_list[k]);
            tmpText.append("\n");
        }
        tmpText.append("\n");
    }
    return tmpText;
}

// display menus and read the choice
int Menu::read_option_number()
{
    int in_num;

    while(true)
    {
        if( !top_text.isEmpty() ) { cout << top_text << endl ; }

        if( !top_prompt.isEmpty() ) { cout << top_prompt << endl ; }

		// display menus
        cout << toString() ;

        if( !bottom_text.isEmpty() ) { cout << bottom_text << endl ; }
		
		// display "?->"
        cout << literal;

        if( !bottom_prompt.isEmpty()  ) { cout << bottom_prompt; }
        cin >> in_num;

		//validate input, in a case that characters are inputed. 
		if (cin.fail())
		{
			cout << "Please enter an integer number, not character(s) and floating point numbers" << endl;
			cin.clear();
			cin.ignore(80, '\n');
			continue;
		}

        if( count > 0)
        {
            if (in_num >= 1 && in_num <= count)
            {
                return  in_num;
            } else {
                cout << "Invalid choice " << in_num << ". It must be in the range [1," << count << "]" << endl;
            }
        }else
		{
            return  in_num;
        }
    }

}


// set a string(Text&) into 'top_prompt'
void Menu::set_top_prompt(const Text & t)
{
    top_prompt.set(t);
}

// set a string(Text&) into 'bottom_prompt'
void Menu::set_bottom_prompt(const Text & t)
{
    bottom_prompt.set(t);
}

// set a string(Text&) into 'top_text'
void Menu::set_top_message(const Text & m)
{
    top_text.set(m);
}

// set a string(Text&) into 'bottom_text'
void Menu::set_bottom_message(const Text & m)
{
    bottom_text.set(m);
}

// clear the 'top_prompt' string
void Menu::clear_top_prompt()
{
    top_prompt.set("");
}

// clear the 'bottom_prompt' string
void Menu::clear_bottom_prompt()
{
    bottom_prompt.set("");
}

// clear the 'top_text' string
void Menu::clear_top_message()
{
    top_text.set("");
}

// clear the 'bottom_text' string
void Menu::clear_bottom_message()
{
    bottom_text.set("");
}

// return ture/false if the Text array is empty
bool Menu::isEmpty() const
{
    return count == 0;
}
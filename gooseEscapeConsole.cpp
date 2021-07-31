/*
  STUDENTS: Don't modify this code unless you are comfortable with C++ classes.
    If you want to modify the size of the console, change the constants in the
    gooseEscaoeUtil.hpp file.
*/
  
#include <iostream>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeConsole.hpp"

Console:: Console()
{
    // each string element in messages is initialized to "" by the string constructor
    messageRow = 0;
}
	
void Console:: writeLine(string new_message_to_print)
{
    //clear the whole console
    terminal_clear_area(MIN_CONSOLE_X, MIN_CONSOLE_Y, NUM_CONSOLE_X, NUM_CONSOLE_Y);

    // update content of console rows
    if(messageRow < NUM_CONSOLE_Y)
    {
        messages[messageRow] = new_message_to_print;
        messageRow++;
    }
    else
    {
        for(int index = 0; index < NUM_CONSOLE_Y-1; index++)
            messages[index] = messages[index+1];
        messages[NUM_CONSOLE_Y-1] = new_message_to_print;
    }
		
    // output all message rows to the console		 
    for(int line = 0; line < NUM_CONSOLE_Y; line++)
        terminal_print(MIN_CONSOLE_X, MIN_CONSOLE_Y + line, messages[line].c_str());
		
    terminal_refresh();
}

/*
    Having more than one console is a bad idea.  So you really shouldn't be
    calling these functions.
*/
Console:: Console(Console const & src)
{
    // memory allocation of array is fixed, so copy constructor and assignment operator are the same
    *this = src;
}
	
Console& Console:: operator=(Console const & src)
{
    cerr << "Warning!  You have more than one Console object" << endl;
    for (int index = 0; index < NUM_CONSOLE_Y; index++)
        messages[index] = src.messages[index];
    messageRow = src.messageRow;
    return *this;
}


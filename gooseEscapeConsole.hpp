/*
  STUDENTS: Don't modify this code unless you are comfortable with C++ classes.
    If you want to modify the size of the console, change the constants in the
    gooseEscaoeUtil.hpp file.
*/

#ifndef GOOSE_CONSOLE
#define GOOSE_CONSOLE
#include <iostream>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

class Console
{
  public:
    Console();
    void writeLine(string new_message_to_print);

/*
    Having more than one console is a bad idea.  So you really shouldn't be
    calling these functions.
*/
    Console(Console const & src);
    Console& operator=(Console const & src);


  private:
	string messages[NUM_CONSOLE_Y];
	int messageRow;
};
#endif


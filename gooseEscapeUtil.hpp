//STUDENTS: Be very careful if you decide to change these values

#ifndef GOOSE_UTIL
#define GOOSE_UTIL
/*
With graphics, screens are given an x,y coordinate system with the origin
in the upper left corner.  So it means the coordinate axes are:
---------------->   x direction
|
|
|
|
|
V

y direction 
*/

// Screen layout
const int NUM_SCREEN_X = 80;
const int NUM_SCREEN_Y = 25;
const char SETUP_MESSAGE[] = "window: title='Escape the Goose', size=80x25";  // size needs to match NUM_SCREEN_X and NUM_SCREEN_Y
const int MIN_SCREEN_X = 0;
const int MIN_SCREEN_Y = 0;
const int MAX_SCREEN_X = NUM_SCREEN_X - 1;
const int MAX_SCREEN_Y = NUM_SCREEN_Y - 1;

// Play area layout
const int NUM_BOARD_X = NUM_SCREEN_X;  // needs to be <= NUM_SCREEN_X
const int NUM_BOARD_Y = NUM_SCREEN_Y - 4;  // needs to be < NUM_SCREEN_Y
const int MIN_BOARD_X = 0;
const int MIN_BOARD_Y = 0;
const int MAX_BOARD_X = NUM_BOARD_X - 1;
const int MAX_BOARD_Y = NUM_BOARD_Y - 1;
const char DRAW_COLOUR[] = "white";

// Console message area layout
const int NUM_CONSOLE_X = NUM_SCREEN_X - 1;  // needs to be <= NUM_SCREEN_X
const int NUM_CONSOLE_Y = NUM_SCREEN_Y - NUM_BOARD_Y;
const int MIN_CONSOLE_X = 1;
const int MIN_CONSOLE_Y = MAX_BOARD_Y + 1;
const int MAX_CONSOLE_X = MAX_SCREEN_X;
const int MAX_CONSOLE_Y = MAX_SCREEN_Y;

#endif

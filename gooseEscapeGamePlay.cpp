#include <iostream>
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActor.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

/*
    This file is all about the game world.  You will modify this to add
    functionality to your game, first to get it working, and later to make
    it fun.
    
    If you add or modify functions, be sure to update the prototypes in the
    gooseEscapeGamePlay.hpp file.
*/

extern Console out;

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
	
/*
	Print the game world
	
    The purpose of this function is to update the console to reflect the
    current state of the game board. It works by calling the terminal_put(...)
    function once for each of the game board elements, and then calling
    terminal_refresh() once after all elements have been put. Note that empty
    spaces do not need to be drawn.
*/
// function header
void printBoard(int map[HEIGHT][WIDTH]){
	for(int i = 0; i < HEIGHT; i++)
	{
		for(int j = 0; j < WIDTH; j++)
		{
			if(map[i][j] == WINNER)
			{
				terminal_put(j,i,WIN_CHAR);	
			}
			else if(map[i][j] == SHALL_NOT_PASS)
			{
				terminal_put(j,i,WALL_CHAR);
			}
		}	
	}
    
	// after putting items on the game board, refresh the terminal to see the items
	terminal_refresh();
}

/*
    Do something when the goose captures the player

    At the moment the function just checks to see if the player and the goose
    are in the same location.  If you want to attack or do something else, this
    function would need to change.  For example, maybe the two touch each other
    and then fight.  You could use the health that is given in the Actor class,
    and update it.  Fight, run, use weapons, it is up to you!
*/

bool captured(Actor const & player, Actor const & monster)
{
    return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
}

/*
    Move the player to a new location based on the user input
    
    All key presses start with "TK_" then the character.  So "TK_A" is the A
    key that was pressed.  At the moment, only the arrow keys are used,
    but feel free to add more keys that allow the player to do something else
    like pick up a power up.
    
    A look-up table might be useful.

    Going further: You could decide to learn about switch statements
*/
void movePlayer(int key, Actor & player, int map[HEIGHT][WIDTH])
{
    int yMove = 0, xMove = 0;
    if (key == TK_UP)
        yMove = -1;
    else if (key == TK_DOWN)
        yMove = 1;
    else if (key == TK_LEFT)
        xMove = -1;
    else if (key == TK_RIGHT)
        xMove = 1;
        
    if (player.can_move(xMove, yMove) 
      && map[player.get_y() + yMove][player.get_x() + xMove] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

/*
    What other functions do you need to make the game work?  What can you add
    to the basic functionality to make it more fun to play?
*/


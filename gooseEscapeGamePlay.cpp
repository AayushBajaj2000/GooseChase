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
	for(int i = 0; i < HEIGHT; i++) // Looping over the board
	{
		for(int j = 0; j < WIDTH; j++)
		{
			if(map[i][j] == WINNER) // Printing the winner char
			{
				terminal_put(j,i,WIN_CHAR);	
			}
			else if(map[i][j] == SHALL_NOT_PASS) // Printing the wall char
			{
				terminal_put(j,i,WALL_CHAR);
			}
			else if(map[i][j] == POWER) // Printing the powerup char
			{
				terminal_put(j,i,POWER_CHAR);
			}
			else if(map[i][j] == TEL_START) // Printing the teleportation tile char
			{
				terminal_color(color_from_name(TEL_COLOR)); // Get the color
				terminal_put(j,i,TEL_CHAR); // Print the char
				terminal_refresh(); // refresh the terminal
				terminal_color(color_from_name(DRAW_COLOUR)); // Change the color back to white
			}
			else if(map[i][j] == TEL_END) // Printing the teleportation tile char
			{
				terminal_color(color_from_name(TEL_COLOR));
				terminal_put(j,i,TEL_CHAR);
				terminal_refresh();
				terminal_color(color_from_name(DRAW_COLOUR));
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

bool captured(Actor & player, Actor & monster)
{
	if(player.get_health_int() == 50) // if only 1 life left then we check for capture, and end game
	{
		return (player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y());
	}
	else // If 2 lives left then if captured, update health and reset player and goose.
	{
		if(player.get_x() == monster.get_x() 
         && player.get_y() == monster.get_y())
		{	
			player.update_health(-50); // remove 50 off the health
			player.set_location(10,10); // reset the player
			monster.set_location(70,20); // reset the monster
		}
	}
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
    int speed = player.get_speed(); // getting the speed of the player
    if (key == TK_UP) // Changing the speed according to key pressed.
        yMove = -speed;
    else if (key == TK_DOWN)
        yMove = speed;
    else if (key == TK_LEFT)
        xMove = -speed;
    else if (key == TK_RIGHT)
        xMove = speed;
        
    if (player.can_move(xMove, yMove) // If the player can move and move is not a wall then update location
      && map[player.get_y() + yMove][player.get_x() + xMove] != SHALL_NOT_PASS)
        player.update_location(xMove, yMove);
}

/*
    Move the Goose to chase the player.
*/
void moveGoose(Actor & player,Actor & monster,int map[HEIGHT][WIDTH])
{
    int xDist = abs(player.get_x() - monster.get_x());
    int yDist = abs(player.get_y() - monster.get_y());
    
    int xMove = 0, yMove = 0;
    int moveDist = 1;
    
    if(xDist > yDist && player.get_x() > monster.get_x())
	{
		xMove = moveDist;	
	}
	else if(xDist > yDist && player.get_x() < monster.get_x())
	{
		xMove = -moveDist;
	}
	else if(xDist < yDist && player.get_y() > monster.get_y())
	{
		yMove = moveDist;
	}
	else if(xDist < yDist && player.get_y() < monster.get_y())
	{
		yMove = -moveDist;
	}

	if(map[monster.get_y() + yMove][monster.get_x() + xMove] == SHALL_NOT_PASS)
	{
		xMove = xMove * 2;
		yMove = yMove * 2;
	}
	
	if(monster.can_move(xMove, yMove) && 
	map[monster.get_y() + yMove][monster.get_x() + xMove] != WINNER &&
	map[monster.get_y() + yMove][monster.get_x() + xMove] != SHALL_NOT_PASS)
			monster.update_location(xMove, yMove, true);

}
/*
	Function to generate a wall
*/
void generate_wall(int map[HEIGHT][WIDTH], int length, bool isVertical)
{
	if(isVertical) // If the wall is vertical, then make a vertical wall
	{
		int row = rand() % (HEIGHT - length) ; // initializing the start of the wall
		int col = rand() % WIDTH;
		
		for(int x = 0; x < length; x++) // Looping over the length of the wall add the wall on the board
		{
			map[row + x][col] = SHALL_NOT_PASS;
		}
	}
	else // printing a horizontal wall
	{
		int row = rand() % HEIGHT; // intializing the start of the wall
		int col = rand() % (WIDTH - length);
		
		for(int x = 0; x < length; x++) // Looping over the length of the wall to add the wall on the board
		{
			map[row][col + x] = SHALL_NOT_PASS;
		}	
	}
}

/*
	Function to check if the game is over. Compare positions of goose and player.
*/
bool isOver(Actor const & player, int row, int col)
{
	return player.get_x() == col && player.get_y() == row;
}

/*
	Function to check if the player is on the powerup tile if yes the use the powerup.
*/
bool isPower(Actor & player, int row, int col)
{
	if(player.get_x() == col && player.get_y() == row)
	{
		player.update_speed(2); // Increase the speed of the player
		return true;
	}
	return false;
}

/*
	Function to check if the player is on the teleport tile if yes then teleport.
*/
void isTeleport(Actor & player, int row, int col, int row1, int col1)
{
	if(player.get_x() == col && player.get_y() == row) // if on the first tile, then teleport to the second tile.
		player.set_location(col1,row1);
	else if(player.get_x() == col1 && player.get_y() == row1) // If on the second tile, then teleport to the first tile
		player.set_location(col,row);
}

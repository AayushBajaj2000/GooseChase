#include <BearLibTerminal.h>
#include <cmath>
#include <ctime>
#include <iostream>  // Debugging tip:  You can still use cout to put debug messages on the regular console window
#include<string> 
using namespace std;
#include "gooseEscapeUtil.hpp"
#include "gooseEscapeActor.hpp"
#include "gooseEscapeConsole.hpp"
#include "gooseEscapeGamePlay.hpp"

//set up the console.   Don't modify this line!
Console out;

int main()
{
    // Set up for using rand() to generate random numbers (can be deleted if random numbers not used)
    srand(time(NULL));
    
	//Set up the window.  Don't edit these two lines
    terminal_open();
  	terminal_set(SETUP_MESSAGE);

/*
    The code below provides a skeleton of the game play.  You will need to 
    write code for setting up the game board, and playing the game itself.
    You can modify the code given as needed.
    
    Call the functions that you have written in the game play file.
*/
    // declare the game board "map"
	int map[HEIGHT][WIDTH] = {0};

/*
    Initialize locations in the game board to have game features.  This
    would include anything that is static and doesn't move like a wall.  Hard
    coding them like you see below is a poor way to code this.  What if you 
    have many features to add to the game board?  Should you use a loop?  Does
    it make sense to store this information in a file?  Should code be a
    function as well?
*/
	
	// Making a minimum 10 tile length wall
	int wallNum = rand() % 2;
	int tenLength = rand() % 6 + 10;
	
	if(wallNum == 0) // Make a horizontal wall
		generate_wall(map, tenLength, false);
	else // Make a vertical one
		generate_wall(map, tenLength, true);	
	

	// Generating vertical walls with random length
    for(int wall = 0; wall < VERTICAL_WALLS; wall++)
	{
		int length = rand() % 10 + 1;
		generate_wall(map,length, true);	
	}
    //Generating horizontal walls with random length
    for(int wall = 0; wall < HORIZONTAL_WALLS; wall++)
	{
		int length = rand() % 10 + 1;
		generate_wall(map,length, false);	
	}
	
	// Adding the winning character to the board
	int win_row = rand() % 21;
	int win_col = rand() % WIDTH;
	map[win_row][win_col] = WINNER;
	
	// Adding the powerup character to the board
	int power_row = rand() % 21;
	int power_col = rand() % WIDTH;
	map[power_row][power_col] = POWER;
	
	// Adding the teleport tile character to the board
	int tel_row = rand() % 21;
	int tel_col = rand() % WIDTH;
	map[tel_row][tel_col] = TEL_START;

// Adding the second teleport tile character to the board
	int tel1_row = rand() % 21;
	int tel1_col = rand() % WIDTH;
	map[tel1_row][tel1_col] = TEL_END;

    // Call the function to print the game board
  	printBoard(map);
/*
    The player and goose are initialized to the same locations
    (10,10) and (70,20) each time, with health of 100.
    You likely want to change this somehow.
*/
    // make the player
	Actor player(PLAYER_CHAR, 10,10, 100, PLAYER_COLOUR);
	
	// make the goose
	Actor monster(MONSTER_CHAR, 70,20, 100, GOOSE_COLOUR);
    
	// Printing the instructions in the console window
    out.writeLine("Escape the Goose! " + monster.get_location_string());
	out.writeLine("Use the arrow keys to move");
	out.writeLine("If the goose catches you, you lose!");
	out.writeLine("Be careful! Sometimes the goose can jump through walls!");

/*
    This is the main game loop.  It continues to let the player give input
    as long as they do not press escape or close, they are not captured by
    the goose, and they didn't reach the win tile
*/
/*
    All key presses start with "TK_" then the character.  So "TK_A" is the "a"
    key being pressed.
*/
    int keyEntered = TK_A;  // can be any valid value that is not ESCAPE or CLOSE
    time_t current_time,power_time; // Getting the time variables
    
    while(keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE 
                    && !captured(player,monster) && !isOver(player,win_row,win_col))
	{
		current_time = time(NULL); // getting the current time

	    // get player key press
	    keyEntered = terminal_read();

        if (keyEntered != TK_ESCAPE && keyEntered != TK_CLOSE)
        {
            // move the player, you can modify this function
    	    movePlayer(keyEntered,player,map);
	    
    	    // call the goose's chase function
    	    moveGoose(player,monster, map);
    	    
			// Check if player is on the powerup tile
    	    if(isPower(player,power_row,power_col))
				power_time = time(NULL); // start the power time
    	    
			if(current_time - power_time > 2) // powerup is allowed for only 4 seconds
				player.update_speed(1); // setting speed to default speed
    	    
    	    // Check if the player is on the teleportation tile
    	    isTeleport(player, tel_row, tel_col, tel1_row, tel1_col);
    	}
  	}

    if (keyEntered != TK_CLOSE)
    {
      	//once we're out of the loop, the game is over
        out.writeLine("Game has ended");
    
        // Output why:  did the goose get you?  Or did you win?
		if(isOver(player,win_row,win_col)){
			out.writeLine("Congrats! You Won");	// printing if the user wins
			while (terminal_read() != TK_CLOSE);
		}
		else if(player.get_x() == monster.get_x() && player.get_y() == monster.get_y()){
			out.writeLine("Sorry! You Lost");	// printing if the user loses
			while (terminal_read() != TK_CLOSE);		
		}
		
    	// Wait until user closes the window
        while (terminal_read() != TK_CLOSE);
    }

	//game is done, close it  
    terminal_close();
}


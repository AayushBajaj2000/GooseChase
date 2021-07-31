#ifndef GOOSE_ESCAPE_ACTORS
#define GOOSE_ESCAPE_ACTORS
#include <cmath>
using namespace std;
#include <BearLibTerminal.h>
#include "gooseEscapeUtil.hpp"

/*
    Going further:  You can modify this class to contain more characteristics
    of the "actor" (anything that moves in your game) or to change how some of
    the functions work.
*/

class Actor
{
  public:
  // set up default actor - something in the game that moves around the board
    Actor();
    
  // set up actor given player character, location, starting health, and colour
    Actor(char initPlayerChar, int x0, int y0, int health0, const char colour0[]);
    
  // get current x and y position of the actor
    int get_x() const;
    int get_y() const;
    
  // get current x and y position formatted as a string so it can be output to the console
    string get_location_string() const;
    
  // set a new character that will be used for showing the actor, will display after next move
    void change_char(char new_actor_char);
    
  // get current health of actor  
    int get_health_int() const;
    
  // get current health of actor as as tring so it can be output to the console
    string get_health_message() const;
    
  // update health of actor; positive to increase, negative to decrease, with the value force to be > = 0
    void update_health(int change_in_health);
    
  // update colour output for the actor
    void update_colour(const char colour0[]);
    
  // check whether actor can move to new location x + delta_x, y + delta_y
    bool can_move(int delta_x, int delta_y) const;
    
  /* check for whether actor can move, and if so, by defaul clears current location,
     then moves the actor to x + delta_x, y + delta_y, and draws actor */
    void update_location(int delta_x, int delta_y, bool clearCurrentLocation=true);

  // draws actor at current location
    void put_actor() const;
    
  private:
    int actorChar;  // character to display, stored as int to match BearLibTerminal    
    int location_x, location_y;  // location on the game board
    int health;  // current health
    color_t actorColour;
};
#endif

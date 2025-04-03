
#ifndef _CLIMB_GHOST_H
#define _CLIMB_GHOST_H

//-------------------------------------------------------------------------
// * ClimbGhost - A ghost that can climb ladders.
//-------------------------------------------------------------------------

#include "Ghost.h"

using namespace std;

class ClimbGhost : public Ghost
{

    bool isClimbing = false;    // Tracks if the ghost is climbing a ladder
    bool isAboutToClimb = false; // Tracks if the ghost is about to climb a ladder
    bool isClimbingDown = false; // Tracks if the ghost is climbing down a ladder
    bool isClimbingUp = false;   // Tracks if the ghost is climbing up a ladder
public:
    ClimbGhost(int x, int y, char _symbol, Board* _b, int _diffx, int _ydiff = 0) : Ghost(x, y, _symbol, _b, _diffx, _ydiff) {}

    void ClimbLadder(); // Handles the logic for climbing a ladder
    void setisClimbing(bool state) { isClimbing = state; } // Sets the climbing state
    void setisAboutToClimb(bool state) { isAboutToClimb = state; } // Sets the about to climb state	
    bool isAboutToClimbLadder() const { return isAboutToClimb; } // Gets the about to climb state
    bool isClimbingLadder() const { return isClimbing; } // Gets the climbing state
    void move() override; // Handles the movement logic for the ghost based on the game rules

};

#endif 


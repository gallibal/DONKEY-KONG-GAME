#ifndef GHOSTIM_H
#define GHOSTIM_H
#include <vector>
#include <iostream>
#include "ClimbGhost.h"
#include "Board.h"
#include "BasicGhost.h"
using namespace std;


//-------------------------------------------------------------------------------------------------------------
// The Ghostim class manages a group of ghosts in the game.
// Handles ghost initialization, movement, collisions, and interactions with Mario.
//-------------------------------------------------------------------------------------------------------------
class Ghostim
{
    vector<std::unique_ptr<Ghost>> GhostimArray;
    Board* b = nullptr;
    bool Pause = false;
  

public:
    Ghostim(Board& board, vector <pair<Point, char>> pos) : b(&board) {
        setGhostPos(pos);
    }
    bool MoveAll(Mario& mario);                                        // Moves all ghosts and handles their interactions with Mario.

    bool removeGhost(int x, int y);

    bool MarioKillGhost(int x, int y);

    void setGhostPos(vector <pair<Point, char>> pos);                   // Sets the initial positions of all ghosts.

    void resetAll();                                                    // Resets all ghosts to their initial positions.

    void setStop()                                                      // Pauses the movement of the ghosts
    {
        if (Pause == false)
            Pause = true;
    }

    void RemoveStop() { Pause = false; }                                // Resumes the movement of the ghosts

    void isGhostsColliding(Ghost& CurrGhost);                           // Checks if the current ghost is colliding with another object or boundary.

};
#endif




#ifndef GHOST_H
#define GHOST_H
#include "GameObject.h"
#include "Mario.h"
#include "Board.h"

using namespace std;
//-------------------------------------------------------------------------------------------------------------
// The Ghost class represents a ghost object in the game.
// Inherits from GameObject and manages ghost behavior such as movement and direction changes.
//-------------------------------------------------------------------------------------------------------------
class Ghost : public GameObject
{
private:
    GameObject ghost;           // Internal GameObject instance for ghost representation.
    Mario* myMario = nullptr;   // Pointer to the Mario object for interactions (e.g., collision handling).
    bool isChangeDir = false;   // Indicates whether the ghost's direction should be changed.
    bool FirstMove = true;      // Tracks if this is the ghost's first movement.



public:

    // Constructor: Initializes a Ghost object with its position, symbol, board, and movement direction.
    Ghost(int x, int y, char _symbol, Board* _b, int _diffx, int _ydiff = 0) : GameObject(x, y, _symbol, _b, _diffx, _ydiff) {}

    ~Ghost() { delete myMario; } // Destructor: Deletes the Mario object pointer.

    void setStartPos(int startX, int startY)       // Sets the starting position of the ghost.
    {
        setX(startX);
        setY(startY);
    }


    virtual void move() = 0;                                    // Handles the movement logic for the ghost based on the game rules.

    void changeDirection() { setdiffX((-1) * (getdiffX())); }      // Changes the ghost's direction by inverting its current x-direction.

    void setChangeDirState() { isChangeDir = true; }                 // Sets the ghost's direction change state to true.

    bool getChangeDirState()const { return isChangeDir; }

    void setDownChangeDirState() { isChangeDir = false; }           // Resets the ghost's direction change state to false.

    void SetISFirstMove() { FirstMove = false; }                    // Marks the ghost's first movement as complete.

    bool getFirstMove() { return FirstMove; }                       // Resets the ghost's first movement state.



};
#endif
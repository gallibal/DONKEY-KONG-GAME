#ifndef __BARRELS_H
#define __BARRELS_H

#include "Barrel.h"
#include "Board.h"


// The Barrels class manages an array of barrels in the game
class Barrels {
private:

    Board* bBoard = nullptr;                       // Pointer to the game board

    vector <int> lastDirections;                   // Array storing last movement directions for each barrel

    vector <Barrel> barrels;                       // Array of barrels

    int startPosX, startPosY;				      // Starting position of the barrels

    bool Pause = false;                         // Indicates if the game is in pause state

    Barrels& operator=(const Barrels&) = delete;
public:

    // Constructor: Initializes the barrels and links them to the game board
    Barrels(Board& board, int startPosX, int startPosY) : bBoard(&board), startPosX(startPosX), startPosY(startPosY) {}

     //-----------------------------------------------------------------------------------------

    void setStartPos(int x, int y) {
        startPosX = x; startPosY = y;
    }

    bool moveAll(Mario& mario);              // Moves all active barrels and checks for collisions with Mario Return true if mario died somehow

    void reset();                             // Resets all barrels to their default state

    void activateNext();                      // Activates the next barrel in the array

    void setStop()                           // Pauses the movement of barrels
    {
        if (Pause == false)
            Pause = true;
    }
    void RemoveStop() { Pause = false; }       // Resumes the movement of barrels

    bool BarreldiefromHammer(int x, int y);    // Handles the death of barrels from hammers

    void removeBarrel(int i);                  // Removes a barrel from the array

};

#endif
#include "Barrel.h"
#include <iostream>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include "general.h"
#include "Game.h"
#include "board.h"
#include <thread>
#include <chrono>
#include <cstdlib>
#include "Mario.h"



using namespace std;

//-------------------------------------------------------------------------------------------------
// Moves the barrel based on game logic
// Parameters:
// - lastd: The last movement direction of the barrel
// - mario: Reference to the Mario object for collision detection 
//-------------------------------------------------------------------------------------------------

int Barrel::move(int lastd, Mario& mario)
{
    erase();
    if (is_Barrel_HIT_Mario(mario.getX(), mario.getY()))        // Checks if the barrel hits Mario
        return 666;

    //-------- Updates direction based on the board state-------//
    if (lastd == 0)
        setdiffX(lastd);         // Keep the last direction
    else if (getBoard()->getPosition(getX() + getdiffX(), getY()) == DONKEY_KONG && getdiffX() != 0)
        setdiffX((-1) * getdiffX());
    else if (getBoard()->getPosition(getX(), getY() + 1) == RIGHT_SLOPE)
        setdiffX(1);              // Move Right
    else if (getBoard()->getPosition(getX(), getY() + 1) == LEFT_SLOPE)
        setdiffX(-1);             // Move Left
    else if (getBoard()->getPosition(getX(), getY() + 1) == FLOOR || bBoard->getPosition(getX(), getY() + 1) == BARRIER || getY() + 1 == GAME_HEIGHT)
        setdiffX(lastd);         // Keep the last direction

    else if (isFall())
    {
        Falling();
        return lastd;
    }

    if (getBoard()->getPosition(getX() + getdiffX(), getY()) == BARRIER || (getX() + getdiffX() == GAME_WIDTH) || getX() + getdiffX() == 0 ||
        getBoard()->getPosition(getX() + getdiffX(), getY()) == FLOOR || getBoard()->getPosition(getX() + getdiffX(), getY()) == LEFT_SLOPE || getBoard()->getPosition(getX() + getdiffX(), getY()) == RIGHT_SLOPE)
        // Checks if the barrel reaches the board's edge or came to a barrier
    {
        erase();
        Turn_Down_Active();                                  // Deactivates the barrel
        return getdiffX();
    }
    else
    {
        // Update the barrel's position
        setX(getX() + getdiffX());
        setY(getY() + getdiffY());
    }
    if (is_Barrel_HIT_Mario(mario.getX(), mario.getY()))
        return 666;

    if (IsActive == true)     // Draws the barrel at the new position
        draw(BARREL);
    return getdiffX();

}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Checks if the barrel has hit Mario
// Parameters:
//  x: Mario's x-coordinate
//  y: Mario's y-coordinate
// Returns true if the barrel's position matches Mario's position

bool Barrel::is_Barrel_HIT_Mario(int x, int y) const
{
    return ((getX() == x) && (getY() == y));
}

//-------------------------------------------------------------------------------------------------
// Checks if Mario is within a given radius of the barrel
// Parameters:
// - targetX: Mario's x-coordinate
// - targetY: Mario's y-coordinate
// - radius: The explosion radius
// Returns true if Mario is within the specified radius

bool Barrel::isMarioInRadius(int targetX, int targetY, int radius)const
{
    int distanceX = abs(targetX - getX()); // Calculate horizontal distance
    int distanceY = abs(targetY - getY()); // Calculate vertical distance

    // Check if both distances are within the explosion radius
    return (distanceX <= radius) && (distanceY <= radius);
}
//-------------------------------------------------------------------------------------------------
// Handles the falling logic for the barrel
// If the barrel falls more than 8 steps, it explodes

void Barrel::Falling()
{
    erase();
    setY(getY() + 1);                                    // Move the barrel down one step
    draw(BARREL);
    FallCounter += 1;                                    // Increment the fall counter

    if (getBoard()->getPosition(getX(), getY() + 1) != SPACE || getY() + 1 == GAME_HEIGHT)
    {
        if (FallCounter >= 8)                           // Check if the barrel has fallen more than 8 steps
        {    
            SetIsExploded();
            draw(SPACE);
            Turn_Down_Active();                         // Deactivates the barrel
        }
        FallCounter = 0;
    }
}
//-------------------------------------------------------------------------------------------------



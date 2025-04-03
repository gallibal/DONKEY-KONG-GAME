#ifndef  ___BARREL_H
#define ___BARREL_H


#include "board.h"
#include <iostream>
#include "general.h"
#include "GameObject.h"

using namespace std;
class Mario;

class Barrel : public GameObject
{

    GameObject barrel; 				   // Barrel's position

    Mario* myMario = nullptr;

    int FallCounter = 0;             // Counter for fall steps

    bool IsActive = true;           // Barrel's active state

    bool IsExploded = false;         // Indicates if the barrel has exploded

    bool waitToErase = false;        // Indicates if the barrel is waiting to be erased

public:
    // Constructor initializing barrel with position and direction
    Barrel(int x = 0, int y = 0, char _symbol = 'O', Board* _b = nullptr, int _diffx = 0, int _ydiff = 0) : GameObject(x, y, _symbol, _b, _diffx, _ydiff) {}
    //--------------------------------------------------------------------------------------------------------------------------------
    //----------------------------------- Public functions for managing the barrel----------------------------------------------------  


    int move(int lastd, Mario& mario);   // Moves the barrel

    bool isFall() const { return bBoard->getPosition(getX(), getY() + 1) == SPACE; }   // Checks if the barrel is falling

    void Falling();                      // Handles falling


    void Set_Active() { IsActive = true; }        // Activates the barrel

    void Turn_Down_Active() { IsActive = false; } // Deactivates the barrel

    bool Get_IsActive()const { return IsActive; }      // Checks if the barrel is active

    void SetIsExploded() { IsExploded = true; }         // Sets the barrel to "exploded"

    void Turn_Down_IsExploded() { IsExploded = false; } // Deactivates "exploded" state

    bool Get_IsExploded()const { return IsExploded; }        // Checks if the barrel has exploded

    bool is_Barrel_HIT_Mario(int x, int y) const;             // Checks if the barrel hit Mario

    bool isMarioInRadius(int targetX, int targetY, int radius)const;  // Checks if Mario is in explosion radius

};






#endif
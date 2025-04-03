#ifndef _BASIC_GHOST_H
#define _BASIC_GHOST_H


//-------------------------------------------------------------------------
// * BasicGhost - A simple ghost that moves according to basic AI rules.
//-------------------------------------------------------------------------
#include "Ghost.h"

class BasicGhost : public Ghost
{
public:
    BasicGhost(int x, int y, char _symbol, Board* _b, int _diffx, int _ydiff = 0) : Ghost(x, y, _symbol, _b, _diffx, _ydiff) {}

    void move()override;
};
#endif
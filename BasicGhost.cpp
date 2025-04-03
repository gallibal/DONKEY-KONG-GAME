#include "BasicGhost.h"
void BasicGhost::move()
{
    erase();
    int randomNum;

    if (getFirstMove())
    {
        randomNum = rand() % 2;
        if (randomNum % 2 == 0)
            setdiffX(1);
        else
            setdiffX(-1);

        SetISFirstMove();
    }
    else if (getChangeDirState() == false)
    {
        randomNum = rand() % 100;

        if (randomNum < 5)
        {
            changeDirection();
        }
    }
    if (getX() + getdiffX() == 0 || getX() + getdiffX() == GAME_WIDTH || getBoard()->getPosition(getX() + getdiffX(), getY()) == BARRIER || getBoard()->getPosition(getX() + getdiffX(), getY()) == FLOOR
       || getBoard()->getPosition(getX() + getdiffX(), getY()) == LEFT_SLOPE || getBoard()->getPosition(getX() + getdiffX(), getY()) == RIGHT_SLOPE)
    {
        changeDirection();
    }
    else if (getBoard()->getPosition(getX() + getdiffX(), getY() + 1) == SPACE && (getY() + 1 != GAME_HEIGHT))
    {
        changeDirection();
    }
    setX(getX() + getdiffX());
    draw(symbol);
}
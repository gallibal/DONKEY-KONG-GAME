
#include "ClimbGhost.h"

void ClimbGhost::move()
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
        else if (isAboutToClimbLadder() || isClimbingLadder())
        {
            ClimbLadder();


        }
        setisAboutToClimb(false);

    }

    if ((getX() + getdiffX() == 0 || getX() + getdiffX() == GAME_WIDTH || getBoard()->getPosition(getX() + getdiffX(), getY()) == BARRIER || getBoard()->getPosition(getX() + getdiffX(), getY()) == FLOOR ||
        getBoard()->getPosition(getX() + getdiffX(), getY()) == LEFT_SLOPE || getBoard()->getPosition(getX() + getdiffX(), getY()) == RIGHT_SLOPE) && !isClimbingLadder())
    {
        changeDirection();
    }
    else if (getBoard()->getPosition(getX() + getdiffX(), getY()) == LADDER)
    {
        setisAboutToClimb(true);
    }
    else if (getBoard()->getPosition(getX() + getdiffX(), getY() + 1) == SPACE && (getY() + 1 != GAME_HEIGHT) && !isClimbingLadder())
    {
        changeDirection();
    }
    if (!isClimbingLadder())
        setX(getX() + getdiffX());
    draw(CLIMB_GHOST);
}


void ClimbGhost::ClimbLadder()
{

    if (getBoard()->getPosition(getX(), getY()) == LADDER)
    {
        setY(getY() - 1);
        setisClimbing(true);
    }
    else if (getBoard()->getPosition(getX(), getY()) == FLOOR || getBoard()->getPosition(getX(), getY()) == RIGHT_SLOPE || getBoard()->getPosition(getX(), getY()) == LEFT_SLOPE)
    {
        setY(getY() - 1);
    }
    else
    {
        setisClimbing(false);
    }
}


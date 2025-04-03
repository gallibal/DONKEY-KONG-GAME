#ifndef ___GAMEOBJECT_H
#define ___GAMEOBJECT_H

#include <iostream>
#include "Point.h"
#include "Board.h"

using namespace std;


class GameObject //: public Point
{
protected:
	Board* bBoard;
	char symbol;
	int diff_x = 0, diff_y = 0;
	Point p;
public:
	GameObject(int _x = 0, int _y = 0, char _symbol = ' ', Board* b = nullptr, int _diffx = 0, int _diffy = 0) : p(_x, _y), symbol(_symbol), bBoard(b), diff_x(_diffx), diff_y(_diffy) {}
	void setBoard(Board& board)           // Sets the game board
	{
		bBoard = &board;

	}

	void erase()
	{

		if (bBoard->getPosition(getX(), getY()) == LADDER)
			draw(LADDER);
		else if (bBoard->getPosition(getX(), getY()) == DONKEY_KONG)
			draw(DONKEY_KONG);
		else if (bBoard->getPosition(getX(), getY()) == BARREL)
			draw(BARREL);
		else if (bBoard->getPosition(getX(), getY()) == HAMMER && symbol != MARIO)
			draw(HAMMER);
		else if (bBoard->getPosition(getX(), getY()) == WIN_CONDITION_CHAR && symbol != MARIO)
			draw(WIN_CONDITION_CHAR);
		else if (bBoard->getPosition(getX(), getY()) == SURPRISE && symbol != MARIO)
			draw(SURPRISE);
		else if (getBoard()->getPosition(getX(), getY()) == FLOOR)
			draw(FLOOR);
		else if (getBoard()->getPosition(getX(), getY()) == LEFT_SLOPE)
			draw(LEFT_SLOPE);
		else if (getBoard()->getPosition(getX(), getY()) == RIGHT_SLOPE)
			draw(RIGHT_SLOPE);
		else
			draw(SPACE);

	}

	void draw(char c) const
	{
		if (bBoard->isSilentMode() == false)
		{
			gotoxy(p.getX(), p.getY());
			cout << c;
		}	
	}
	Board* getBoard() const { return bBoard; }
	void setdiffX(int x) { diff_x = x; }

	void setdiffY(int y) { diff_y = y; }

	void setdiffPos(int x, int y) { diff_x = x; diff_y = y; }

	int getdiffX() const { return diff_x; }

	int getdiffY() const { return diff_y; }

	void setX(int _x) { p.setX(_x); }

	void setY(int _y) { p.setY(_y); }

	int getX() const { return p.getX(); }

	int getY() const { return p.getY(); }

	void setPos(int _x, int _y) { p.setPos(_x, _y); }
};

#endif
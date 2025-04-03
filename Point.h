#ifndef ___POINT_H
#define ___POINT_H

#include <iostream>

#include "general.h"
using namespace std;

class Point {
	int x, y;
public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

	void draw(char c) const
	{
		gotoxy(x, y);
		cout << c;
	}

	void setX(int _x) { x = _x; }

	void setY(int _y) { y = _y; }

	int getX() const { return x; }

	int getY() const { return y; }

	void setPos(int _x, int _y) { x = _x; y = _y; }

};
#endif 
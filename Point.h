#ifndef _Point_
#define _Point_
#include <iostream>
#include "io_utility.h"


class Point {
	int x, y;
public:

	void set(int _x, int _y) { x = _x;y = _y; };
	int getX() const {return x;}
	int getY() const {return y;}
	void draw(char ch);

};





#endif // !_Point_


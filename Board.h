#ifndef _Board_
#define _Board_
#include <iostream>
#include "Point.h"

class Board {
public:
	enum { ROWS = 20, COLS = 32};
private:
	char board[COLS][ROWS];
public:
	void init(bool isNewBoard, int leftBorder, int rightBorder,Color color);
	char get(const int x,const int y);
	void set(const int x, const int y, const char ch) { board[x][y] = ch; }
	void fullRow(int y, int leftBorder, int rightBorder);
	
};

#endif

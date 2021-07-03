#ifndef _Piece_
#define _Piece_

#include "Point.h"
#include <cstring>
#include "Board.h"

class Piece {
public:
	enum { SIZE = 4, NOCHANGE = 0 };
private:
	Point points[SIZE];
	//Bomb bomb;
public:
	void move(int dir, int& bottom, int shape, int& angle, Board& PlayerP, const char sign, int leftBorder, int rightBorder, bool isFake);
	void init(int shape, int x, const char sign);
	void rotate(int shape, int& angle, bool isClock, Board BoardP, const char sign, bool isFake);
	void drop(Board& BoardP, bool isBomb, const char sign, int leftBorder, int rightBorder);
	bool isCollide(int x[4], int y[4], Board BoardP);
	void moveRightLeft(Board boardP, const char sign, int x[SIZE], int y[SIZE]);
	void i_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock);
	void j_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock);
	void l_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock);
	void s_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock);
	void t_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock);
	void z_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock);
	void bombExplode(Board& boardP, int x, int y, int leftBorder, int rightBorder);
	void getPoints(Point _points[SIZE]);
	void setPoints(int x[SIZE],int y[SIZE]); 
};




#endif

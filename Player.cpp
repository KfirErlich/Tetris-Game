#include "Player.h"
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS_

Player::Player(const char _sign, const char _keys[11], Color _color,const int _startLocation, const int _leftBorder, const int _rightBorder)
{
	startLocation = _startLocation;
	sign = _sign;
	for (int i = 0;i < 11;i++)
	{
		keys[i] = _keys[i];
	}
	color = _color;
	leftBorder = _leftBorder;
	rightBorder = _rightBorder;
}

void Player::move(int& bottom, int shape, int& angle, Board& boardP ,const char sign, int leftBorder, int rightBorder)
{	
	Color c;
	c = getColor();
	setTextColor(c);
	bool isFake = false;
	block.move(diraction, bottom, shape, angle, boardP,sign,leftBorder,rightBorder,isFake);

	return;
}


int Player::getDiraction(const char key)
{
	int j = 0;
	for (int i = 0;i < 5;i += 1)
	{
		if (key == keys[j] || key == keys[j + 1])
			return j;
		j += 2;
	}
	return -1;
}
void Player::init(int shape, int x)
{
	block.init(shape, x, getFigure());
	return;
}

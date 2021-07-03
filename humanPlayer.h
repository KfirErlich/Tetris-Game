#ifndef _HumanPlayer_
#define _HumanPlayer_
#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer (const char sign, const char key[11], Color colors,const int x, const int lBorder, const int rBorder) : Player::Player(sign, key, colors,x,lBorder,rBorder) {}

	void whichDir(char key, int shape, Board& boardP,int& isNewBlock) override;
};

#endif
#include "humanPlayer.h"

void HumanPlayer::whichDir(char key, int shape, Board& boardP, int& isNewBlock)
{
	int dir;

	dir = getDiraction(key);
	setDiraction(dir);
	
}
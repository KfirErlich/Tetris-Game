#ifndef _CompPlayer_
#define _CompPlayer_
#include "Player.h"
#include "ComputerScore.h"


class CompPlayer : public Player
{
private:
	ComputerScore blockScore[12][4];
	int level;
	std::string moves;

public:
	CompPlayer(const char sign, const char key[11], Color colors,const int x,const int lBorder, const int rBorder) : Player:: Player( sign, key, colors, x,lBorder,rBorder ) {}
	void setMoves(std::string _moves) { moves = _moves; }//check
	std::string getMoves() { return moves; }
	int getLvl() { return level; }
	void setLvl(const int _lvl) { level=_lvl; }
	void bestRoute(char& key, int shape, Board boardP,int& isNewBlock);
	void whichDir (char key, int shape, Board& boardP, int& isNewBlock) override;
	std::string findRoute(int shape, Board boardP);
	void breakPointsToXY(Piece& FakeBlock, int x[4], int y[4],Board boardP,int offset);
	void setRoute(std::string& route, int& offsetX);
	void calculateDistance(Piece fakeBlock,int whichPlace, int& offsetX,Board boardP);
	void calculateScore(int& whichPlace, int& numOfRotates,int originBumpiness,int originHoles);
	void calculateHeights(Board boardP,int& bumpiness);
	int calculateFullRows(int x[4], int y[4], Board boardP,int index,int whichRotate);
	int calculateBumpiness(int x[4], int y[4], Board boardP);
	int calculateHoles(int x[4], int y[4], Board boardP, bool isOrigin);
	int smartBomb(int x[4], int y[4], Board boardP);
};

#endif
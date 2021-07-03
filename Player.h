#ifndef _Player_
#define _Player_
#include "Piece.h"

class Player {
public:
	enum { SIZE = 4, DEFAULT_DIR = -1, XP1 = 5, XP2 = 20, NOCHANGE = 0};

protected:
	Piece block;
	char sign;
	int startLocation;
	char keys[11];
	int leftBorder;
	int rightBorder;

private:

	int diraction = 0;
	Color color;
	
public:

	Player(const char _sign, const char _keys[11], Color _color, const int startLocation,const int leftBorder,const int rightBorder);

	virtual void init(int shape,int x);

	void setColors(const Color c) { color = c; }

	virtual Color getColor(){return color;}

	virtual void setFigure(const char ch){sign = ch;}

	virtual void setStartLocation(const int x){startLocation = x;}

	virtual char getFigure() const {return sign;}

	virtual int getStartLocation()const {return startLocation;}
	
	virtual int getLeftBorder() const {return leftBorder;}
	
	virtual int getRightBorder() const {return rightBorder;}

	virtual void setLvl(const int lvl) { return;}

	virtual void whichDir(char key, int shape, Board& boardP, int& isNewBlock) { return; }
	
	void move(int& bottom, int shape, int& angle, Board& playerP,const char sign, int leftBorder, int rightBorder);
	
	int getDiraction (const char key);
	
	void setDiraction(int dir){diraction = dir;}
};


#endif


#ifndef _TetGame_
#define _TetGame_
#define _CRT_SECURE_NO_WARNINGS

#include "io_utility.h"
#include "Player.h"
#include "Board.h"
#include "CompPlayer.h"
#include "humanPlayer.h"

class TheTetrisGame {
	enum { ESC = 27, EXIT = 9, INSTRUCTIONS = 8, NOCOLORS = 6, HUMAN_VS_HUMAN = 1, HUMAN_VS_COMPUTER = 2, COMPUTER_VS_COMPUTER = 3, CONTINUE = 4, DEFAULTKEY = -1 };
	enum { LEFTBORDERP1 = 0, LEFTBORDERP2 = 15, RIGHTBORDERP1 = 13, RIGHTBORDERP2 = 28, BOMB = 7 };
	int whichMode;
	Board boardP1, boardP2;
public:
	void menu();
	int getWhichMode() { return whichMode; }
	void setWhichMode(const int _mode) { whichMode = _mode; }
	void init(bool isNewBoard,Color colorP1,Color colorP2);
	void run(bool &isPaused,Player* player1, Player* player2, int mode);
	bool isGameOver(Board boardP1, Board boardP2,bool& isPaused);
	int compLvl();
	void withColors(Player* player1, Player* player2, Player* player3, Player* player4);
};


#endif

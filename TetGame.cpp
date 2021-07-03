#include "TetGame.h"
void TheTetrisGame::menu()
{
	Player* player1 = new HumanPlayer('X', "aAdDsSwWxX", Color::WHITE,Player::XP1,LEFTBORDERP1,RIGHTBORDERP1);
	Player* player2 = new HumanPlayer('O', "jJlLkKiImM", Color::WHITE, Player::XP2,LEFTBORDERP2,RIGHTBORDERP2);
	Player* player3 = new CompPlayer('X', "aAdDsSwWxX", Color::WHITE, Player::XP1,LEFTBORDERP1,RIGHTBORDERP1);
	Player* player4 = new CompPlayer('O', "jJlLkKiImM", Color::WHITE, Player::XP2,LEFTBORDERP2,RIGHTBORDERP2);


	static bool instructionFlag = true;
	bool isPaused = false;
	int whichMode=0;
	int compLevel;

	while (instructionFlag)
	
	{
		setTextColor(Color::WHITE);
		clear_screen();
		int option;

		std::cout << "WELCOME TO TETRIS \n SELECT AN OPTION: " << std::endl;
		std::cout << "1. HUMAN VS HUMAN " << std::endl;
		std::cout << "2. HUMAN VS COMPUTER " << std::endl;
		std::cout << "3. COMPUTER VS COMPUTER " << std::endl;

		if(isPaused)
			std::cout << "4. CONTINUE A PAUSED GAME " << std::endl;

		std::cout << "8. PRESENT INSTRUCTIONS AND KEYS " << std::endl;
		std::cout << "9. EXIT " << std::endl;
		std::cout << " ENJOY :) " << std::endl;
		std::cin >> option;

		while (option != HUMAN_VS_HUMAN && option != HUMAN_VS_COMPUTER && option != COMPUTER_VS_COMPUTER && option != CONTINUE && option != INSTRUCTIONS && option != EXIT)
		{
			std::cout << "YOU CHOSE A WRONG OPTION, PLEASE SELECT AN OPTION FROM THE MENU  " << std::endl;
			std::cin >> option;
		}

		switch (option)
		{
		case HUMAN_VS_HUMAN: //1

			instructionFlag = true;
			setWhichMode(option);
			clear_screen();
			withColors(player1, player2, player3, player4);
			init(true, player1->getColor(),player2->getColor());
			run(isPaused,player1,player2,option);
			break;

		case HUMAN_VS_COMPUTER://2

			setWhichMode(option);
			clear_screen();
			compLevel=compLvl();
			player4->setLvl(compLevel);
			instructionFlag = true;
			clear_screen();
			withColors(player1, player2, player3, player4);
			init(true, player1->getColor(), player4->getColor());
			run(isPaused,player1,player4,option);
			break;

		case COMPUTER_VS_COMPUTER://3

			setWhichMode(option);
			clear_screen();
			compLevel = compLvl();
			player3->setLvl(compLevel);
			clear_screen();
			compLevel = compLvl();
			player4->setLvl(compLevel);
			instructionFlag = true;
			clear_screen();
			withColors(player1, player2, player3, player4);
			init(true, player3->getColor(), player4->getColor());
			run(isPaused,player3,player4,option);
			break;

		case CONTINUE://4
			clear_screen();
			whichMode = getWhichMode();
			instructionFlag = true;

			if (whichMode == 1)
			{
				init(false, player1->getColor(), player2->getColor());
				run(isPaused, player1, player2, option);
			}
			if (whichMode == 2)
			{
				init(false, player1->getColor(), player4->getColor());
				run(isPaused, player1, player4, option);
			}
			if (whichMode == 3)
			{
				init(false, player3->getColor(), player4->getColor());
				run(isPaused, player3, player4, option);
			}
			break;

		case INSTRUCTIONS:
			clear_screen();
			char ch;
			std::cout << "The goal is to make full horizontal lines\n with the different shaped blocks that fall into the game area\n and avoid the blocks stack and reach to the edge of the board\n" << std::endl;
			std::cout << "LEFT player keys: \n           LEFT - A | RIGHT - D | DROP - X | ROTATE CLOCKWISE - S | ROTATE COUNTER CLOCKWISE - W \n" << std::endl;
			std::cout << "RIGHT player keys: \n           LEFT - J | RIGHT - L | DROP - M | ROTATE CLOCKWISE - K | ROTATE COUNTER CLOCKWISE - I \n" << std::endl;
			std::cout << "PAUSE - ESC " << std::endl;
			std::cout << "PRESS ANY KEY AND THAN ENTER TO GO BACK TO MENU " << std::endl;
			std::cin >> ch;

			break;

		case EXIT:
			instructionFlag = false;

			delete player1;
			delete player2;
			delete player3;
			delete player4;

			clear_screen();
			std::cout << "THANK YOU FOR PLAYING, HOPE YOU ENJOYED :)" << std::endl;

		}
	}
}

void TheTetrisGame::init(bool isNewBoard, Color colorP1,Color colorP2)
{
		boardP1.init(isNewBoard,LEFTBORDERP1, RIGHTBORDERP1,colorP1);
		boardP2.init(isNewBoard, LEFTBORDERP2, RIGHTBORDERP2,colorP2);
}
bool TheTetrisGame::isGameOver(Board boardP1, Board boardP2,bool& isPaused)
{
	char ch;
	for (int i = 0;i < RIGHTBORDERP2;i++)
	{
		if (boardP1.get(i, 2) == 'X' && boardP2.get(i, 2) == 'O')
		{
			setTextColor(Color::WHITE);
			clear_screen();
			std::cout << "WOW! IT'S A TIE!! \n " << std::endl;
			std::cout << "PRESS ANY KEY AND THAN ENTER TO GO BACK TO MENU " << std::endl;
			std::cin >> ch;
			isPaused = false;
			return false;
		}
		else if (boardP1.get(i, 1) == 'X')
		{
			setTextColor(Color::WHITE);
			clear_screen();
			std::cout << "PLAYER 2 WINS!\n" << std::endl;
			std::cout << "PRESS ANY KEY AND THAN ENTER TO GO BACK TO MENU " << std::endl;
			std::cin >> ch;
			isPaused = false;
			return false;
		}
		else if (boardP2.get(i, 1) == 'O')
		{
			setTextColor(Color::WHITE);
			clear_screen();
			std::cout << "PLAYER 1 WINS!\n" << std::endl;
			std::cout << "PRESS ANY KEY AND THAN ENTER TO GO BACK TO MENU " << std::endl;
			std::cin >> ch;
			isPaused = false;
			return false;
		}
	}
	return true;
}

void TheTetrisGame::run(bool& isPaused, Player* player1, Player* player2, int mode)
{
	char key = 0;
	int dir;
	int shapeP1= rand() % 7;
	int shapeP2= rand() % 7;;
	int bottom1 = 0, bottom2 = 0;
	int anglep1 = 0, anglep2 = 0;
	int isBombX=1,isBombO=1;	
	int isNewBlockP1 = 0;
	int isNewBlockP2 = 0;

	while (isGameOver(boardP1, boardP2, isPaused))
	{
		if (bottom1 == 0)
		{
			isBombX = rand() % 20;

			if (isBombX == 11)
			{
				player1->setFigure('B');
				player1->init(BOMB, player1->getStartLocation());
				shapeP1=BOMB;
			}
			else
			{
				if(player1->getFigure()!=('X'))
					player1->setFigure('X');

				shapeP1 = rand() % 7;
				player1->init(shapeP1, player1->getStartLocation());
			}
		}
		
		if (bottom2 == 0)
		{
			isBombO = rand() % 20;
			
			if (isBombO == 13)
			{
				player2->setFigure('B');
				player2->init(BOMB, player2->getStartLocation());
				shapeP2 = BOMB;
			}
			else
			{
				if (player2->getFigure() != ('O'))
					player2->setFigure('O');

				shapeP2 = rand() % 7;
				player2->init(shapeP2, player2->getStartLocation());
			}
		}
		
		bottom1 = bottom2 = 0;
		char key=0;

		while (bottom1 != 1 && bottom2 != 1 && key != ESC)
		{
			
			if (_kbhit())
			{
				key = _getch();

				player1->whichDir(key,shapeP1,boardP1,isNewBlockP1);
				player2->whichDir(key,shapeP2,boardP2, isNewBlockP2);

			}
			else
			{
				key = DEFAULTKEY;
				player1->whichDir(key, shapeP1, boardP1, isNewBlockP1);
				player2->whichDir(key, shapeP2, boardP2, isNewBlockP2);
			}
			
			player1->move(bottom1, shapeP1, anglep1, boardP1, player1->getFigure(), LEFTBORDERP1, RIGHTBORDERP1);
			player2->move(bottom2, shapeP2, anglep2, boardP2, player2->getFigure(), LEFTBORDERP2, RIGHTBORDERP2);

			Sleep(300);
		}
		
		if (key == ESC)//check resuming or exit 
		{
			isPaused = true;// change it to a data member
			return;
		}

		if (bottom1 == 1 && bottom2 == 0)
		{
			anglep1 = 0;
			bottom1 = 0;
			bottom2 = 1;
			isBombX = 1;
			isNewBlockP1 = 0;
		}

		else if (bottom2 == 1 && bottom1 == 0)
		{
			anglep2 = 0;
			bottom2 = 0;
			bottom1 = 1;
			isBombO = 1;
			isNewBlockP2 = 0;

		}
		else if (bottom1 == 1 && bottom2 == 1)
		{
			anglep1 = anglep2 = 0;
			bottom1 = 0;
			bottom2 = 0;
			isBombX = 0;
			isBombO = 0;
			isNewBlockP1= isNewBlockP2 = 0;

		}
	}
}

int TheTetrisGame::compLvl()
{
	int mode;
	std::cout << "CHOOSE COMPUTER LEVEL: " << std::endl;
	std::cout << "PRESS 1 FOR - BEST \nPRESS 2 FOR - GOOD \nPRESS 3 FOR - NOVICE " << std::endl;
	std::cin >> mode;
	return mode;
	

}

void TheTetrisGame::withColors(Player* player1, Player* player2, Player* player3, Player* player4)
{
	clear_screen();
	int withColor;
	std::cout << "DO YOU WANT GAME WITH COLORS? " << std::endl;
	std::cout << "PRESS 1 FOR - YES \nPRESS 2 FOR - NO \n " << std::endl;

	std::cin >> withColor;
	if (withColor == 1)
	{
		player1->setColors(Color::LIGHTCYAN);
		player2->setColors(Color::LIGHTRED);
		player3->setColors(Color::LIGHTGREEN);
		player4->setColors(Color::RED);
	}
	else if(withColor==2)
	{
		player1->setColors(Color::WHITE);
		player2->setColors(Color::WHITE);
		player3->setColors(Color::WHITE);
		player4->setColors(Color::WHITE);
	}
	clear_screen();
}
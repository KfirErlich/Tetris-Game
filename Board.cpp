#include "Board.h"

void Board::init(bool isNewBoard, int leftBorder,int rightBorder,Color color)
{
	if (isNewBoard)
	{
		for (int i = 0;i < COLS-4;i++)//without limits
		{
			for (int j = 0;j < ROWS;j++) {
				board[i][j] = ' ';
			}
		}
	}

	else
	{
		
		setTextColor(color);

		char ch;
		{
			for (int j = 1; j < ROWS; j++)
			{
				for (int i = leftBorder+1; i < rightBorder; i++)
				{
					ch = get(i, j);
					gotoxy(i, j);
					std::cout << ch;
				}
			}
		}
	}

	setTextColor(WHITE);

		for (int i = leftBorder;i <= rightBorder;i++)//up
		{
			gotoxy(i, 0);
			std::cout << '_' << std::endl;
			set(i, 0, '_');
		}
		for (int i = leftBorder+1;i < rightBorder;i++)//down
		{
			gotoxy(i, ROWS - 1);
			std::cout << '_' << std::endl;
			set(i, ROWS - 1, '_');
		}
		for (int i = 1;i < ROWS;i++)//left
		{
			gotoxy(leftBorder, i);
			std::cout << '|' << std::endl;
			set(leftBorder, i, '|');
		}
		for (int i = 1;i < ROWS;i++)//right
		{
			gotoxy(rightBorder, i);
			std::cout << '|' << std::endl;
			set(rightBorder, i, '|');
		}

	return;
}

char Board::get(const int x, const int y)
{
	return board[x][y];
}

void Board::fullRow(int y,int leftBorder, int rightBorder)
{
	char down, up;
	bool flag = true;

	for (int i = leftBorder+1;i < rightBorder;i++)
	{
		if (get(i,y) == ' ')
			flag = false;	
	}
	if (flag)
	{
		for (int i = leftBorder +1;i < rightBorder;i++)
		{
			set(i, y, ' ');
		}

		for (int i = y - 1;i >0;i--)
		{
			for (int j = leftBorder+1;j < rightBorder;j++)
			{
				board[j][i + 1] = board[j][i];
				up = board[j][i];
				gotoxy(j, i + 1);
				std::cout << up;
				
			}
		}
	}

}
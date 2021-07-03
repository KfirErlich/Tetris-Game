#include "Piece.h"
#include "Board.h"


void Piece::move(int dir, int& bottom, int shape, int& angle, Board& BoardP,const char sign, int leftBorder, int rightBorder,bool isFake)
{
	int x[SIZE], y[SIZE];
	int whichAngel = 0;
	bool isClock;
	bool isBomb = 0;

	for (int i = 0;i < SIZE;i++)
	{
		x[i] = points[i].getX();
		y[i] = points[i].getY();
	}
	switch (dir)
	{
	case 0://LEFT

		for (int i = 0;i < SIZE;i++)
		{
			x[i] -= 1;
		}
		moveRightLeft(BoardP, sign, x, y);
		
		break;
	case 2://RIGHT
		
		for (int i = 0;i < SIZE;i++)
		{
			x[i] += 1;
		}
		moveRightLeft(BoardP, sign, x, y);
		break;

	case 4: //RotateClockwise
		isClock = true;
		
			rotate(shape, angle, isClock,BoardP,sign,isFake);
			angle++;
			break;
		
	case 6://counterClockWise

		isClock = false;
		rotate(shape, angle, isClock ,BoardP,sign,isFake);
		angle--;
		break;
	case 8:
		
		drop(BoardP,isBomb,sign,leftBorder,rightBorder);
		bottom = 1;
		

		break;
	default:

		for (int i = 0;i < 4;i++)
		{
			if (BoardP.get(x[i], y[i] + 1) != ' ')
			{
				bottom = 1;
					
				if (sign == 'B')
					bombExplode(BoardP,x[0],y[0],leftBorder,rightBorder);
				else 
				{
					for (int j = 0;j < SIZE;j++)
					{
						int currX = points[j].getX();
						int currY = points[j].getY();
						BoardP.set(currX, currY, sign);
					}
					for (int j = 0;j < 10;j++)
					{
						int currY = points[0].getY()-4+j;
						if(currY>0 && currY<=Board::ROWS-2)
						BoardP.fullRow(currY, leftBorder, rightBorder);
					}
				}
					
				return;
			}
		}
		
		for (int i = 0;i < SIZE;i++) {
			points[i].draw(' ');
			BoardP.set(points[i].getX(), points[i].getY(), ' ');
		}
			

		for (int i = 0;i < SIZE;i++)
		{

			y[i] += 1;
			points[i].set(x[i], y[i]);
			points[i].draw(sign);
				
		}
		break;

	}
	return;
}
void Piece::moveRightLeft(Board BoardP, const char sign, int x[SIZE], int y[SIZE])
{
	for (int i = 0;i < SIZE;i++)
	{

		if (BoardP.get(x[i], y[i])!=' ')
			return;
	}
	for (int i = 0;i < SIZE;i++)
		points[i].draw(' ');

	for (int i = 0;i < SIZE;i++)
	{
		points[i].set(x[i], y[i]);
		points[i].draw(sign);

	}
}
void Piece::drop(Board& BoardP, bool isBomb,const char sign,int leftBorder, int rightBorder)
{
	bool flag = true;
	int x;
	int y;
	while (flag)
	{
		for (int i = 0;i < 4;i++)
		{
			x = points[i].getX();
			y = points[i].getY();

			if ((BoardP.get(x, y + 1) != ' '))
			{
				flag = false;
				break;
			}
			else
			{
				flag = true;
			}
		}
		if (flag)
		{
			for(int i=0;i<SIZE;i++)
				points[i].draw(' ');
			for (int i = 0;i < SIZE;i++)
			{
				int x = points[i].getX();
				int y = points[i].getY();
				points[i].set(x, y + 1);
				points[i].draw(sign);
			}
		}
	}
	if (sign == 'B')
	{
		bombExplode(BoardP, x, y, leftBorder, rightBorder);
		return;
	}

	for (int i = 0;i < SIZE;i++)
	{
		BoardP.set(points[i].getX(), points[i].getY(), sign);
	}
	
	for (int j = 0;j < 10;j++)
	{
		int currY = points[0].getY() - 4 + j;
		if (currY > 0 && currY <= Board::ROWS - 2)
			BoardP.fullRow(currY, leftBorder, rightBorder);
	}

	return;
}

void Piece::rotate(int shape, int& angle,bool isClock,Board BoardP,const char sign,bool isFake)
{
	int x[4], y[4];
	if (angle == 4)
		angle = 0;
	if (angle == -1)
		angle = 3;
	int whichAngle = angle;

	for (int i = 0; i < SIZE;i++)
	{
		x[i] = points[i].getX();
		y[i] = points[i].getY();
	}

	switch (shape)
	{
	case 0://----
		if (whichAngle == 2)
			whichAngle = 0;
		else if (whichAngle == 3)
			whichAngle = 1;

		i_Block(whichAngle, x, y, isClock);
		break;

	case 1://---|

		j_Block(whichAngle, x, y, isClock);
		break;

	case 2://|---

		l_Block(whichAngle, x, y, isClock);
		break;

	case 3://+

		t_Block(whichAngle, x, y, isClock);
		break;
	case 4://case number 4 square
		break;
	case 5:// --
			// --
		if (whichAngle == 2)
			whichAngle = 0;
		else if (whichAngle == 3)
			whichAngle = 1;

		z_Block(whichAngle, x, y, isClock);
		break;

	case 6://--
		  //--
		if (whichAngle == 2)
			whichAngle = 0;
		else if (whichAngle == 3)
			whichAngle = 1;
		s_Block(whichAngle, x, y, isClock);
		break;

	case 7://bomb
		break;
	}

	if (!isFake)
	{
		if (isCollide(x, y, BoardP))
			return;
		for (int i = 0;i < SIZE;i++)
			points[i].draw(' ');

		for (int i = 0;i < SIZE;i++)
		{
			points[i].set(x[i], y[i]);
		}

		for (int i = 0;i < SIZE;i++)
		{
			points[i].draw(sign);
		}
	}
	else
	{
		for (int i = 0;i < SIZE;i++)
		{
			points[i].set(x[i], y[i]);
		}
	}
}

void Piece::i_Block(int whichAngle, int x[SIZE], int y[SIZE],bool isClock)
{
	switch (whichAngle)
	{

	case 0:
		x[0] += 2, x[1] += 1, x[2] += NOCHANGE, x[3] += -1;
		y[0] += -1, y[1] += NOCHANGE, y[2] += 1, y[3] += 2;

		break;
	case 1:
		x[0] += -2, x[1] += -1, x[2] += NOCHANGE, x[3] += 1;
		y[0] += 1, y[1] += NOCHANGE, y[2] += -1, y[3] += -2;

		break;

	}
}

void Piece:: j_Block(int whichAngle, int x[SIZE], int y[SIZE],bool isClock)
{
	switch (whichAngle)
	{
	case 0:
		if (!isClock)//counterClockwise
		{
			x[0] += NOCHANGE, x[1] += -1, x[2] += -2, x[3] += -1;
			y[0] += 2, y[1] += 1, y[2] += NOCHANGE, y[3] += -1;

		}
		else //clockWise
		{
			x[0] += 1, x[1] += NOCHANGE, x[2] += -1, x[3] += -2;
			y[0] += NOCHANGE, y[1] += 1, y[2] += 2, y[3] += 1;

		}

		break;
	case 1:
		if (!isClock)//counterClockwise
		{
			x[0] += -1, x[1] += NOCHANGE, x[2] += 1, x[3] += 2;
			y[0] += NOCHANGE, y[1] += -1, y[2] += -2, y[3] += -1;

		}
		else //clockWise
		{
			x[0] += 1, x[1] += NOCHANGE, x[2] += -1, x[3] += NOCHANGE;
			y[0] += 2, y[1] += 1, y[2] += NOCHANGE, y[3] += -1;
		}


		break;
	case 2:
		if (!isClock)//counterClockwise
		{
			x[0] += -1, x[1] += NOCHANGE, x[2] += 1, x[3] += NOCHANGE;
			y[0] += -2, y[1] += -1, y[2] += NOCHANGE, y[3] += 1;

		}
		else //clockWise
		{
			x[0] += -2, x[1] += -1, x[2] += NOCHANGE, x[3] += 1;
			y[0] += NOCHANGE, y[1] += -1, y[2] += -2, y[3] += -1;

		}

		break;
	case 3:
		if (!isClock)//counterClockwise
		{
			x[0] += 2, x[1] += 1, x[2] += NOCHANGE, x[3] += -1;
			y[0] += NOCHANGE, y[1] += 1, y[2] += 2, y[3] += 1;

		}
		else //clockWise
		{
			x[0] += NOCHANGE, x[1] += 1, x[2] += 2, x[3] += 1;
			y[0] += -2, y[1] += -1, y[2] += NOCHANGE, y[3] += 1;

		}


		break;
	}

}

void Piece:: l_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock)
{
	switch (whichAngle)
	{
	case 0:
		if (!isClock)//counterClockwise
		{
			x[0] += 1, x[1] += NOCHANGE, x[2] += -1, x[3] += -2;
			y[0] += 1, y[1] += 2, y[2] += 1, y[3] += NOCHANGE;

		}
		else //clockWise
		{
			x[0] += NOCHANGE, x[1] += 1, x[2] += NOCHANGE, x[3] += -1;
			y[0] += -1, y[1] += NOCHANGE, y[2] += 1, y[3] += 2;

		}

		break;
	case 1:
		if (!isClock)//counterClockwise
		{
			x[0] += NOCHANGE, x[1] += -1, x[2] += NOCHANGE, x[3] += 1;
			y[0] += 1, y[1] += NOCHANGE, y[2] += -1, y[3] += -2;

		}
		else //clockWise
		{
			x[0] += 1, x[1] += NOCHANGE, x[2] += -1, x[3] += -2;
			y[0] += 1, y[1] += 2, y[2] += 1, y[3] += NOCHANGE;
		}

		break;
	case 2:
		if (!isClock)//counterClockwise
		{
			x[0] += -1, x[1] += NOCHANGE, x[2] += 1, x[3] += 2;
			y[0] += -1, y[1] += -2, y[2] += -1, y[3] += NOCHANGE;

		}
		else //clockWise
		{
			x[0] += NOCHANGE, x[1] += -1, x[2] += NOCHANGE, x[3] += 1;
			y[0] += 1, y[1] += NOCHANGE, y[2] += -1, y[3] += -2;
		}

		break;
	case 3:
		if (!isClock)//counterClockwise
		{
			x[0] += NOCHANGE, x[1] += 1, x[2] += NOCHANGE, x[3] += -1;
			y[0] += -1, y[1] += NOCHANGE, y[2] += 1, y[3] += 2;
		}
		else //clockWise
		{
			x[0] += -1, x[1] += NOCHANGE, x[2] += 1, x[3] += 2;
			y[0] += -1, y[1] += -2, y[2] += -1, y[3] += NOCHANGE;

		}

		break;
	}
}

void Piece:: s_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock)
{
	switch (whichAngle)
	{
	case 0:
		x[0] += NOCHANGE, x[1] += -1, x[2] += NOCHANGE, x[3] += -1;
		y[0] += -1, y[1] += NOCHANGE, y[2] += 1, y[3] += 2;


		break;
	case 1:
		x[0] += NOCHANGE, x[1] += 1, x[2] += NOCHANGE, x[3] += 1;
		y[0] += 1, y[1] += NOCHANGE, y[2] += -1, y[3] += -2;

		break;
	}
}

void Piece:: t_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock)
{
	switch (whichAngle)
	{
	case 0:
		if (!isClock)//counterClockwise
		{
			x[0] += NOCHANGE, x[1] += -1, x[2] += -2, x[3] += NOCHANGE;
			y[0] += 2, y[1] += 1, y[2] += NOCHANGE, y[3] += NOCHANGE;

		}
		else //clockWise
		{
			x[0] += 1, x[1] += NOCHANGE, x[2] += -1, x[3] += -1;
			y[0] += NOCHANGE, y[1] += 1, y[2] += 2, y[3] += NOCHANGE;

		}

		break;
	case 1:
		if (!isClock)//counterClockwise
		{
			x[0] += -1, x[1] += NOCHANGE, x[2] += 1, x[3] += 1;
			y[0] += NOCHANGE, y[1] += -1, y[2] += -2, y[3] += NOCHANGE;

		}
		else //clockWise
		{
			x[0] += 1, x[1] += NOCHANGE, x[2] += -1, x[3] += 1;
			y[0] += 1, y[1] += NOCHANGE, y[2] += -1, y[3] += -1;

		}


		break;
	case 2:
		if (!isClock)//counterClockwise
		{
			x[0] += -1, x[1] += NOCHANGE, x[2] += 1, x[3] += -1;
			y[0] += -1, y[1] += NOCHANGE, y[2] += 1, y[3] += 1;

		}
		else //clockWise
		{
			x[0] += -2, x[1] += -1, x[2] += NOCHANGE, x[3] += NOCHANGE;
			y[0] += 1, y[1] += NOCHANGE, y[2] += -1, y[3] += 1;
		}


		break;
	case 3:
		if (!isClock)//counterClockwise
		{
			x[0] += 2, x[1] += 1, x[2] += NOCHANGE, x[3] += NOCHANGE;
			y[0] += -1, y[1] += NOCHANGE, y[2] += 1, y[3] += -1;


		}
		else //clockWise
		{
			x[0] += NOCHANGE, x[1] += 1, x[2] += 2, x[3] += NOCHANGE;
			y[0] += -2, y[1] += -1, y[2] += NOCHANGE, y[3] += NOCHANGE;
		}

		break;
	}
}

void Piece:: z_Block(int whichAngle, int x[SIZE], int y[SIZE], bool isClock)
{
	switch (whichAngle)
	{
	case 0:
		x[0] += 1, x[1] += NOCHANGE, x[2] += -1, x[3] += -2;
		y[0] += NOCHANGE, y[1] += 1, y[2] += NOCHANGE, y[3] += 1;

		break;

	case 1:
		x[0] += -1, x[1] += NOCHANGE, x[2] += 1, x[3] += 2;
		y[0] += NOCHANGE, y[1] += -1, y[2] += NOCHANGE, y[3] += -1;

		break;
	}
}


bool Piece:: isCollide(int x[4], int y[4],Board BoardP)
{
	for (int i = 0;i < SIZE ;i++)
	{
		if(BoardP.get(x[i],y[i])!=' ')
			return true;
	}
	return false;
}

void Piece::init(int shape, int x, const char sign) {


	switch (shape)
	{
	case 0://i

		for (int i = 0;i < SIZE;i++)
		{
			points[i].set(x + i, 1);
		}

		break;

	case 1://j

		points[0].set(x, 1);
		points[1].set(x + 1, 1);
		points[2].set(x + 2, 1);
		points[3].set(x + 2, 2);

		break;
	case 2://L

		points[0].set(x, 2);
		points[1].set(x, 1);
		points[2].set(x + 1, 1);
		points[3].set(x + 2, 1);

		break;

	case 3://+

		points[0].set(x, 1);
		points[1].set(x + 1, 1);
		points[2].set(x + 2, 1);
		points[3].set(x + 1, 2);


		break;

	case 4: //square
		points[0].set(x, 1);
		points[1].set(x, 2);
		points[2].set(x + 1, 1);
		points[3].set(x + 1, 2);

		break;

	case 5://z

		points[0].set(x, 1);
		points[1].set(x + 1, 1);
		points[2].set(x + 1, 2);
		points[3].set(x + 2, 2);

		break;

	case 6://s

		points[0].set(x, 2);
		points[1].set(x + 1, 2);
		points[2].set(x + 1, 1);
		points[3].set(x + 2, 1);

		break;

	case 7://BOMB
		
		points[0].set(x, 2);
		points[1].set(x, 2);
		points[2].set(x, 2);
		points[3].set(x, 2);

		

		break;
	}
	for (int i = 0;i < SIZE;i++)
	{
		points[i].draw(sign);
	}
	return;
}
void Piece::bombExplode(Board& boardP, int x, int y, int leftBorder, int rightBorder)
{
	int leftBorderBomb, rightBorderBomb, stopper;
	leftBorderBomb = x - 4;
	rightBorderBomb = x + 4;
	stopper = y;
	char tempCh;

	for(int k=0;k<9;k++)
	{
		for (int i = leftBorderBomb;i <= rightBorderBomb; i++)
		{

			if (i < rightBorder && i > leftBorder && stopper + 4 < boardP.ROWS - 1)
			{
				//tempCh = boardP.get(i, stopper-5);
				boardP.set(i, stopper + 4, ' ');
				gotoxy(i, stopper + 4);
				std::cout << ' ';
			}
		}
		stopper--;
		if (stopper < 1)
			break;
	}
}

void Piece::getPoints(Point _points[SIZE])
{
	for (int i = 0;i < SIZE;i++)
	{
		_points[i] = points[i];
	}
}

void Piece::setPoints(int x[SIZE], int y[SIZE])
{
	for (int i = 0; i < SIZE;i++)
	{
		points[i].set(x[i], y[i]);
	}
}
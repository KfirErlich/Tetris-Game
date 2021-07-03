#include "CompPlayer.h"

void CompPlayer::whichDir(char key, int shape, Board& boardP, int& isNewBlock)
{
	int dir;
	
	bestRoute(key, shape, boardP, isNewBlock);// The function creates if it is a new block a route and return a key - where to move every turn, or just return the next key

	dir = getDiraction(key);

	if (level == 2)
	{
		int num = rand() % 40;
		if (num == 18)
			dir = rand() % 8;
	}
	if (level == 3)
	{
		int num = rand() % 20;
		if (num == 13)
			dir = rand() % 8;
	}
	setDiraction(dir);
}

void CompPlayer::bestRoute(char& key,int shape,Board boardP,int &isNewBlock)
{
	std::string route = getMoves();
	int size = route.size();
	
	if (isNewBlock==0)
	{
		route.assign(findRoute(shape, boardP));
		size = route.size();
		setMoves(route);
	}
	if (isNewBlock >= size)
	{
		key = keys[8];
	}
	else
		key = route[isNewBlock];
	
	isNewBlock++;
	

}


std::string CompPlayer::findRoute(int shape, Board boardP)
{
	Piece fakeBlock = block;
	int x[SIZE], y[SIZE];
	int firstX[SIZE];
	int tempAngle = 0;
	int offsetX;
	int angle = 0;
	bool isFullRow = false;
	std::string route;
	bool foundPlace = false;
	int whichPlace, numOfRotates;
	int originBumpiness = 0, howManyRows, currBumpiness = 0, originHoles = 0, currHoles = 0;
	route.push_back('b');//first move 1 down
	int tempMaxBomb = 0, maxBomb = 0, locationMaxBomb = 0;

	calculateHeights(boardP, originBumpiness);//calculate the height of every colomn before all sets
	originHoles = calculateHoles(x, y, boardP, false);
	
	
		if (sign == 'B' && level == 1)
		{
			for (int i = 0; i < 12; i++)
			{
				breakPointsToXY(fakeBlock, x, y, boardP, i);
				tempMaxBomb = smartBomb(x, y, boardP);
				if (tempMaxBomb > maxBomb)
				{
					maxBomb = tempMaxBomb;
					locationMaxBomb = i;
				}
				fakeBlock = block;
			}
			offsetX =locationMaxBomb-XP1+1;
			fakeBlock = block;
		}

		else
		{
			for (int i = 0; i < 12; i++)//check COLS place
			{
				for (int j = 0; j < 4; j++)//rotation
				{
					breakPointsToXY(fakeBlock, x, y, boardP, i);

					if (fakeBlock.isCollide(x, y, boardP))
					{
						howManyRows = -5;//can't be there
						blockScore[i][j].setNewHeight(boardP.ROWS);
					}
					else
					{
						currBumpiness = calculateBumpiness(x, y, boardP);
						howManyRows = calculateFullRows(x, y, boardP, i,j);
						currHoles = calculateHoles(x, y, boardP, true);
					}

					blockScore[i][j].setBumpiness(currBumpiness);
					blockScore[i][j].setCompleteLines(howManyRows);
					blockScore[i][j].setHoles(currHoles);

					fakeBlock = block;
					currBumpiness = 0;
					currHoles = 0;

					while (tempAngle <= angle)
					{
						fakeBlock.rotate(shape, tempAngle, 1, boardP, sign, true);
						tempAngle++;
						if (tempAngle == 4)
							break;
					}
					angle++;
					tempAngle = 0;
				}
				angle = 0;
			}
			
			calculateScore(whichPlace, numOfRotates, originBumpiness, originHoles);

			fakeBlock = block;
			angle = 0;

			while (angle < numOfRotates)
			{
				fakeBlock.rotate(shape, angle, 1, boardP, sign, true);
				angle++;
				route.push_back(keys[4]);
			}

			calculateDistance(fakeBlock, whichPlace, offsetX, boardP);
		}

	setRoute(route, offsetX);
	
	return route;

}

void CompPlayer::breakPointsToXY(Piece& fakeBlock, int x[4], int y[4],Board boardP,int offset)
{
	Point points[4];
	fakeBlock.getPoints(points);
	bool canGoLeft = true;
	
	for (int i = 0; i < SIZE ;i++)
	{
		x[i] = points[i].getX();
		y[i] = points[i].getY();
	}
	
	if (y[0] == 0 || y[1] == 0 || y[2] == 0 || y[3] == 0)
	{
		for (int i = 0; i < SIZE; i++)
		{
			y[i]++;
		}
	}

	while (canGoLeft)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (boardP.get(x[i]-1, y[i]) != ' ')
				canGoLeft = false;
		}

		if (canGoLeft)
		{
			for (int i = 0;i < SIZE;i++)
				x[i]--;
		}
	}
	for (int i = 0; i < SIZE; i++)
	{

		x[i] += offset;
	}

	bool canGoDown = true;
	while (canGoDown)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (boardP.get(x[i], y[i] + 1) != ' ')
				canGoDown = false;
		}

		if (canGoDown)
		{
			for (int i = 0;i < SIZE;i++)
				y[i]++;
		}
	}

	fakeBlock.setPoints(x, y);
}

void CompPlayer::calculateDistance(Piece fakeBlock,int whichPlace, int& offsetX,Board boardP)
{
	Point points[4];
	fakeBlock.getPoints(points);
	int firstX[4];
	int y[4];
	int afterMoveX[4];

	for (int i = 0; i < SIZE; i++)
	{
		firstX[i] = points[i].getX();
		y[i] = points[i].getY();
	}
	if (y[0] == 0 || (y[1] == 0) || (y[2] == 0) || (y[3] == 0))
	{
		for (int i = 0; i < SIZE; i++)
		{
			y[i]++;
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		afterMoveX[i] = firstX[i];
	}

	int i;
	bool canGoLeft = true;

	while (canGoLeft)
	{
		for (int i = 0; i < SIZE; i++)
		{
			if (boardP.get(afterMoveX[i] - 1, y[i]) != ' ')
				canGoLeft = false;
		}

		if (canGoLeft)
		{
			for (int i = 0;i < SIZE;i++)
				afterMoveX[i]--;
		}
	}
	
	for (int i = 0; i < whichPlace; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			afterMoveX[j]++;
		}
	}
	offsetX = afterMoveX[0]-firstX[0];
}

void CompPlayer::setRoute(std::string& route,int& offsetX)
{
	
	if (offsetX < 0)
	{
		for (int i = 0; i < abs(offsetX); i++)
		{
			route.push_back(keys[0]);
		}
	}
	else
	{
		for (int i = 0; i < offsetX; i++)
		{
			route.push_back(keys[2]);
		}
	}
	route.push_back(keys[8]);
}


void CompPlayer::calculateHeights(Board boardP,int& bumpiness)
{
	int tempHeight = 0;
	int tempX = getLeftBorder() + 1;
	int tempY = 1;
	int boardHeights[12];

	for (int i = 0; i < 12; i++)
	{
		while (boardP.get(tempX, tempY) == ' ')
		{
			tempY++;
		}
		for (int j = 0; j < SIZE; j++)
		{
			blockScore[i][j].setHeight(Board::ROWS-1-tempY);
		}
		boardHeights[i] = Board::ROWS-1- tempY;
		tempX++;
		tempY = 1;
	}
	for (int i = 0; i < 11; i++)
	{
		bumpiness += abs(boardHeights[i] - boardHeights[i + 1]);
	}

}

int CompPlayer::calculateFullRows(int x[4], int y[4], Board boardP,int index,int whichRotate)
{
	int howManyRows = 0;
	bool fullRow=true;
	int tempy = 1;
	int height = Board::ROWS-2 - blockScore[index][0].getheight();
	for (int i = 0; i < SIZE; i++)
	{
		boardP.set(x[i], y[i], '$');
	}

	while (boardP.get(leftBorder+1+index, tempy) == ' ')
		tempy++;

	for (int i = 0; i < SIZE; i++)
	{
		if (tempy > y[i])
			tempy = y[i];
	}

	blockScore[index][whichRotate].setNewHeight(Board::ROWS - 1 - tempy);

	for (int j = height+4;j >= height-4;j--)
	{
		if (j <= Board::ROWS-2)
		{
			for (int i = leftBorder + 1; i < rightBorder; i++)
			{
				if (boardP.get(i, j) == ' ')
					fullRow = false;
			}
			if (fullRow)
				howManyRows++;
		}
		fullRow = true;
	}
	return howManyRows;
}

void CompPlayer::calculateScore(int& whichPlace, int& numOfRotates,int originBumpiness, int originHoles)
{
	int bestPlace, bestRotate;
	int tempScore,tempBestScore=0;
	int bestScoreEveryX[12];
	int theBestRotate[12];


	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int score = (100 *( blockScore[i][j].getCompleteLines()) + (5*(Board::ROWS - blockScore[i][j].getNewHeight())) + (2*(originBumpiness - blockScore[i][j].getBumpiness())+ 8*(originHoles - blockScore[i][j].getHoles())));
			blockScore[i][j].setScore(score);
		}
	}

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tempScore = blockScore[i][j].getScore();
			
			if (tempBestScore < tempScore)
			{
				tempBestScore = tempScore;
				theBestRotate[i] = j;
			}

		}
		bestScoreEveryX[i] = tempBestScore;
		tempBestScore = 0;
		tempScore = 0;
	}
	tempScore = 0;
	tempBestScore = 0;

	for (int i = 0; i < 12; i++)
	{
		tempScore = bestScoreEveryX[i];
		if (tempBestScore < tempScore)
		{
			tempBestScore = tempScore;
			whichPlace = i;
			numOfRotates = theBestRotate[i];//check if this is the correct one
		}

	}

}

int CompPlayer::calculateBumpiness(int x[4], int y[4], Board boardP)
{
	int currBumpiness = 0;
	
	for (int i = 0; i < SIZE; i++)
	{
		boardP.set(x[i], y[i], '$');
	}
	
	int tempHeight = 0;
	int tempX = getLeftBorder() + 1;
	int tempY = 1;
	int boardHeights[12];

	for (int i = 0; i < 12; i++)
	{
		while (boardP.get(tempX, tempY) == ' ')
		{
			tempY++;
		}

		boardHeights[i] = Board::ROWS-1-tempY;
		tempX++;
		tempY = 1;
	}
	for (int i = 0; i < 11; i++)
	{
		currBumpiness += (abs(boardHeights[i] - boardHeights[i + 1]));
	}
	return currBumpiness;

}

int CompPlayer::calculateHoles(int x[4], int y[4], Board boardP,bool isOrigin)
{
	int howManyHoles = 0;
	int counter=0;
	int tempX = getLeftBorder() + 1;
	int tempY = 1;

	if (isOrigin)
	{
		for (int i = 0; i < SIZE; i++)
		{
			boardP.set(x[i], y[i], '$');
		}
	}

	for (int i = 0; i < 12; i++)
	{
		while (boardP.get(tempX, tempY)== ' ')
		{
			tempY++;
		}
		tempY--;

		for(int j = Board::ROWS-2; j >= tempY; j--)
		{
			if (boardP.get(tempX, j) == ' ')
			{
				if (boardP.get(tempX, j - 1) != ' ')
					howManyHoles++;
			}
		}

		tempX++;
		tempY = 1;
	}


	return howManyHoles;
}

int CompPlayer::smartBomb(int x[4], int y[4], Board boardP)
{

	int counter = 0;
	
	boardP.set(x[0], y[0], '$');

	for (int i = x[0]-4; i < x[0]+5; i++)
	{	
		if (i > leftBorder && i < rightBorder)
		{
			for (int j = y[0] - 4; j < y[0] + 5; j++)
			{
				if (j < Board::ROWS - 1 && j>0)
				{
					if (boardP.get(i, j) != ' ')
					{
						counter++;
					}
				}
			}
		}
	}
	return counter;
}
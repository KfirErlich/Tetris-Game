#include "Point.h"

void Point::draw(char ch)
{
	gotoxy(x, y);
	std::cout << ch << std::endl;

}


#include"snake.h"

SNAKE& SNAKE::eat( POINT p)
{

	POINT p_temp = position[length - 1];
	move();
	position[length] = p_temp;
	length += 1;
	
	return *this;
}

void SNAKE::move( )
{
	if (length > 1)
	{
		for (int i = length - 1; i > 0; i--)
			position[i] = position[i - 1];
		switch (v)
		{
		case L:
			position[0].x -= 1;
			break;
		case R:
			position[0].x += 1;
			break;
		case T:
			position[0].y -= 1;
			break;
		case B:
			position[0].y += 1;
			break;
		}
	}
	else switch (v)
	{
	case L:
		position[0].x -= 1;
		break;
	case R:
		position[0].x += 1;
		break;
	case T:
		position[0].y -= 1;
		break;
	case B:
		position[0].y += 1;
		break;
	}
	
	
}

void SNAKE::change_v(int i)
{
	v = i;
}
int SNAKE::getlength()
{
	return length;
}
POINT* SNAKE::getposition()
{
	return position;
}
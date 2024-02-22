#pragma once
#include<windows.h>

#ifndef SNAKE_H

#define SNAKE_H

#define L 1
#define R 2
#define T 3
#define B 4

struct FOOD
{
	POINT p;
	BOOL state = 1;

	FOOD(POINT p):
		p(p){}

};



class SNAKE
{
private:
	int length = 2;
	POINT* position;

	int v = R;

public:
	SNAKE(POINT* p) :
		 position(p) {}

	SNAKE& eat( POINT );
	void move();
	void change_v(int);
	int getlength();
	POINT* getposition();

};




#endif // !SNAKE_H

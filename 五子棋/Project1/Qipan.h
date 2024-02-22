#pragma once
#include<windows.h>
#include<vector>

#define B 1;
#define W 0;

struct Qizi
{
	Qizi() = default;
	Qizi(POINT& p,int c):
		position(p),color(c) { }

	POINT position = { 0,0 };
	int color=W;
	int r = 10;
};

class Qipan
{
public:

	Qipan() = default;
	Qipan(std::vector<Qizi> q,int s):
		qi(q),size(s) { }

	bool check();
	void paint(HDC& ,int cx,int cy);

	void add(POINT&,int );
	POINT tran(POINT&, int cx, int cy);

private:
	std::vector<Qizi> qi;
	int size = 20;
};


#include<set>
#include "Qipan.h"
#include<cmath>

bool Qipan::check()
{
	std::vector<Qizi> q(qi);
	
	int jude = 0;

	auto end = q.back().position;


	std::vector<POINT> t1;
	std::vector<POINT> t2;
	std::vector<POINT> t3;
	std::vector<POINT> t4;

	for (auto first = q.begin(); first != q.cend()-1; first++)
	{
		if (first->position.x==end.x)
		{
			t1.push_back(first->position);
		}
		if (first->position.y == end.y)
		{
			t2.push_back(first->position);
		}
		if(first->position.x - end.x == first->position.y - end.y)
		{
			t3.push_back(first->position);
		}
		if (first->position.x - end.x + first->position.y - end.y == 0)
		{
			t4.push_back(first->position);
		}
	}
	if (t1.size() == 0&& t2.size() == 0&& t3.size() == 0&& t4.size()==0)
		return 0;

	int t1j1 = 0;
	int t1j2 = 0;
	int t1j3 = 0;
	int t1j4 = 0;
	int t1j5 = 0;
	for (auto t1f = t1.begin(); t1f != t1.end(); t1f++)
	{
		if (pow((t1f->y - end.y), 2) <= 4)
			t1j1 += 1;
		if ((t1f->y < end.y) && pow((t1f->y - end.y), 2) <= 16)
			t1j2 += 1;
		if ((t1f->y > end.y) && pow((t1f->y - end.y), 2) <= 16)
			t1j3 += 1;
		if ((t1f->y < end.y && pow((t1f->y - end.y), 2) <= 9) || t1f->y - end.y == 1)
			t1j4 += 1;
		if ((t1f->y > end.y && pow((t1f->y - end.y), 2) <= 9) || t1f->y - end.y == -1)
			t1j5 += 1;
	}

	if ((t1j1 == 4 )|| (t1j2 == 4 )|| (t1j3 == 4)||(t1j4==4)||(t1j5==4))
		jude += 1;


	int t2j1 = 0;
	int t2j2 = 0;
	int t2j3 = 0;
	int t2j4 = 0;
	int t2j5 = 0;
	for (auto t2f = t2.begin(); t2f != t2.end(); t2f++)
	{
		if (pow((t2f->x - end.x), 2) <= 4)
			t2j1 += 1;
		if ((t2f->x < end.x) && pow((t2f->x - end.x), 2) <= 16)
			t2j2 += 1;
		if ((t2f->x > end.x) && pow((t2f->x - end.x), 2) <= 16)
			t2j3 += 1;
		if ((t2f->x < end.x && pow((t2f->x - end.x), 2) <= 9) || (t2f->x - end.x == 1))
			t2j4 += 1;
		if ((t2f->x > end.x && pow((t2f->x - end.x), 2) <= 9) || (t2f->x - end.x == -1))
			t2j5 += 1;
	}

	if ((t2j1 == 4) || (t2j2 == 4) || (t2j3 == 4) || (t2j4 == 4) || (t2j5 == 4))
		jude += 1;


	int t3j1 = 0;
	int t3j2 = 0;
	int t3j3 = 0;
	int t3j4 = 0;
	int t3j5 = 0;
	for (auto t3f = t3.begin(); t3f != t3.end(); t3f++)
	{
		if (pow((t3f->y - end.y), 2) <= 4)
			t3j1 += 1;
		if ((t3f->y < end.y) && pow((t3f->y - end.y), 2) <= 16)
			t3j2 += 1;
		if ((t3f->y > end.y) && pow((t3f->y - end.y), 2) <= 16)
			t3j3 += 1;
		if ((t3f->y < end.y && pow((t3f->y - end.y), 2) <= 9) || t3f->y - end.y == 1)
			t3j4 += 1;
		if ((t3f->y > end.y && pow((t3f->y - end.y), 2) <= 9) || t3f->y - end.y == -1)
			t3j5 += 1;
	}

	if ((t3j1 == 4) || (t3j2 == 4) || (t3j3 == 4) || (t3j4 == 4) || (t3j5 == 4))
		jude+=1;
	

	int t4j1 = 0;
	int t4j2 = 0;
	int t4j3 = 0;
	int t4j4 = 0;
	int t4j5 = 0;
	for (auto t4f = t4.begin(); t4f != t4.end(); t4f++)
	{
		if (pow((t4f->y - end.y), 2) <= 4)
			t4j1 += 1;
		if ((t4f->y < end.y) && pow((t4f->y - end.y), 2) <= 16)
			t4j2 += 1;
		if ((t4f->y > end.y) && pow((t4f->y - end.y), 2) <= 16)
			t4j3 += 1;
		if ((t4f->y < end.y && pow((t4f->y - end.y), 2) <= 9) || (t4f->y - end.y == 1))
			t4j4 += 1;
		if ((t4f->y > end.y && pow((t4f->y - end.y), 2) <= 9) || (t4f->y - end.y == -1))
			t4j5 += 1;
	}


	if ((t4j1 == 4) || (t4j2 == 4) || (t4j3 == 4) || (t4j4 == 4) || (t4j5 == 4))
		jude += 1;

	t1.clear();
	t2.clear();
	t3.clear();
	t4.clear();

	q.clear();

	if (jude)
		return 1;
	else
		return 0;
}

void Qipan::paint(HDC& hDC,int cx,int cy)
{
	int d = cy / (size+2);

	for (int i = 0; i <= size; i++)
	{
		MoveToEx(hDC,  d, (i + 1) * d, NULL);
		LineTo(hDC, (size + 1) * d, (i + 1) * d);

		MoveToEx(hDC, (i + 1) * d, d, NULL);
		LineTo(hDC, (i + 1) * d, (size + 1) * d);
	}

	
	
	for(auto first = qi.begin(); first != qi.end();first++)
	{
		HDC _hDC = hDC;
		HPEN oldpen;
		HBRUSH oldbrush;
		HBRUSH hb;
		if (first->color)
		{
			oldpen=(HPEN)SelectObject(_hDC, CreatePen(0, 0, RGB(0, 0, 0)));
			oldbrush=(HBRUSH)SelectObject(_hDC, CreateSolidBrush(RGB(0, 0, 0)));
		}
		else
		{
			oldpen = (HPEN)SelectObject(_hDC, CreatePen(0, 0, RGB(1, 1, 1)));
			oldbrush = (HBRUSH)SelectObject(_hDC, CreateSolidBrush(RGB(255, 255, 255)));
		}

		Ellipse(_hDC, (first->position.x)*d  - first->r,
			(first->position.y)*d  - first->r,
			(first->position.x)*d  + first->r,
			(first->position.y)*d  + first->r);
		DeleteObject(SelectObject(_hDC, oldpen));
		DeleteObject(SelectObject(_hDC, oldbrush));
	}
}

void Qipan::add(POINT& p, int c)
{
	Qizi qizi;
	qizi.position = p;
	qizi.color = c;
	if (p.x <= size+1 && p.y <= size+1 &&p.x>0 &&p.y>0)
	{
		qi.push_back(qizi);
	}
	
}

POINT Qipan::tran(POINT& p, int cx, int cy)
{
	int d = cy / (size + 2);

	POINT np;
	if (p.x % d <= d / 2)
		np.x = p.x / d;
	else
		np.x = p.x / d + 1;

	if (p.y % d <= d / 2)
		np.y = p.y / d;
	else
		np.y = p.y / d + 1;

	
	return np;
}

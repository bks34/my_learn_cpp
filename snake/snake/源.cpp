#include<windows.h>
#include<tchar.h>
#include<iostream>

#include"resource.h"
#include"snake.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);


void paint_snake(HDC hdc, HWND hwnd, SNAKE& s);
void paint_food(HDC hdc, HWND hwnd, FOOD& food);

BOOL check(SNAKE& s, FOOD& food);

static const POINT p_s[100]= { {24,13},{23,13} };
static  POINT p[100] = { {24,13},{23,13} };

static POINT p_f = { 26,13 };

static SNAKE s = SNAKE( p);
static FOOD food = FOOD(p_f);
static HDC hdc;
static HPEN hPen;
static HBRUSH hBrush;
static PAINTSTRUCT ps;
static RECT rect;
static HINSTANCE hInstance;



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Snake");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;//创建一个窗口类wndclass

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;


	RegisterClass(&wndclass);// 注册窗口

	hwnd = CreateWindow(szAppName,
		TEXT("Snake"),
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,//WS_VSCROLL加竖直滚动条
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);//创建窗口

	ShowWindow(hwnd,iCmdShow);//SW_SHOWMAXIMIZED表示显示时为最大化窗口，还有SW_SHOWNORMAL,SW_SHOWMINNOACTIVE

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
		
			

	return msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

	switch (message)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		GetClientRect(hwnd, &rect);
		
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LBUTTON:
			InvalidateRect(hwnd, NULL, FALSE);
			break;

		case 0x57:
		case VK_UP:
			s.change_v(T);
			break;
		case 0x41:
		case VK_LEFT:
			s.change_v(L);
			break;
		case 0x53:
		case VK_DOWN:
			s.change_v(B);
			break;
		case 0x44:
		case VK_RIGHT:
			s.change_v(R);
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		return 0;

	case WM_PAINT:

		
		
		hdc = BeginPaint(hwnd, &ps);

		paint_snake(hdc, hwnd, s);
		food.state=check(s, food);
		
		if (food.state == 0)
		{
			if ((s.getposition()[0].x == food.p.x)
				&& (s.getposition()[0].y == food.p.y))
				s.eat(food.p);

			food.p.x = rand() % 47 + 1;
			food.p.y = rand() % 22 + 1;
			food.state = check(s, food);
		}
		paint_food(hdc, hwnd, food);
		
		
		
		EndPaint(hwnd, &ps);
		
		if (s.getposition()[0].x < 48
			&& s.getposition()[0].x>0
			&& s.getposition()[0].y > 0
			&& s.getposition()[0].y < 23)
		{
			s.move();

			for (int i = 0; i < s.getlength(); i++)
			{
				for (int j = i + 1; j < s.getlength(); j++)
				{
					if ((s.getposition()[i].x == s.getposition()[j].x)
						&& (s.getposition()[i].y == s.getposition()[j].y))
					{
						DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)DlgProc);

					}
				}
			}

			Sleep(150);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else
		{
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)DlgProc);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		return 0;
		


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			*p = *p_s;
			s = SNAKE( p);
			EndDialog(hDlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			SendMessage(GetParent(hDlg), WM_DESTROY, NULL, NULL);
			return TRUE;
		}
		break;

	}

	return 0;
}

void paint_snake(HDC hdc, HWND hwnd, SNAKE& s)
{
	
	hPen = CreatePen(BS_SOLID, 2, RGB(255, 100, 0));
	hBrush = CreateSolidBrush(RGB(255, 100, 0));
	SelectObject(hdc, hPen);
	SelectObject(hdc, hBrush);

	for (int i = 0; i < s.getlength(); i++)
	{
		int p_to_s = (rect.right - rect.left) / 48;

		Ellipse(hdc, s.getposition()[i].x * p_to_s, s.getposition()[i].y * p_to_s,
			(s.getposition()[i].x + 1) * p_to_s, (s.getposition()[i].y + 1) * p_to_s);

	}
	
}

void paint_food(HDC hdc, HWND hwnd, FOOD& f)
{
	
	

		hPen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
		hBrush = CreateSolidBrush(RGB(0, 255, 0));
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);

		int p_to_s = (rect.right - rect.left) / 48;
		Ellipse(hdc, f.p.x * p_to_s,
			f.p.y * p_to_s,
			(f.p.x + 1) * p_to_s,
			(f.p.y + 1) * p_to_s);

	
}

BOOL check(SNAKE& s, FOOD& food)
{
	

	for (int i = 0; i < s.getlength(); i++)
	{
		if ((s.getposition()[i].x == food.p.x)
			&& (s.getposition()[i].y == food.p.y))
			return 0;
		else
			return 1;
	}

	
}
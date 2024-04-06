#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include<stdlib.h>
#include<math.h>
#include"TransFunc.h"

#define MAX_BF_SZIE 1024

wchar_t func[MAX_BF_SZIE];
char f[MAX_BF_SZIE];

void DrawFunc(HWND hwnd, int o_x, int o_y, double step, char* func);


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;
	TCHAR appaName[] = TEXT("Draw Functions");

	wndclass.style = CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = appaName;

	RegisterClass(&wndclass);

	hWnd = CreateWindow(appaName,
		TEXT("Draw Functions"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, SW_NORMAL);

	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


void DrawFunc(HWND hwnd, int o_x, int o_y, double step, char* func)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	GetWindowRect(hwnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	hdc = BeginPaint(hwnd, &ps);
	MoveToEx(hdc, 10, o_y, NULL);
	LineTo(hdc, width - 10, o_y);
	MoveToEx(hdc, o_x, height/8, NULL);
	LineTo(hdc, o_x, height-10);

	for (int i = height - 10; i > height/8; i--)
	{
		if (!((i - o_y) % (int)(1 / step)))
		{
			MoveToEx(hdc, o_x - 0.1 / step,i, 0);
			LineTo(hdc, o_x + 0.1 / step,i);
			int y = -1*step * (i - o_y);
			char out[10];
			_itoa(y, out, 10);
			wchar_t w_out[12];
			mbstowcs(w_out, out, 12);
			if(y)
				TextOut(hdc,o_x - 0.3 / step, i,w_out, strlen(out));
		}
	}
	for (int i = 10; i < width-20; i++)
	{
		MoveToEx(hdc, i, (int)(-TransFunc(func, step *(i-o_x))/step)+o_y, NULL);
		LineTo(hdc, i + 2,(int)(-TransFunc(func, step * (i + 1-o_x))/step)+o_y);
		if (!((i - o_x)%(int)(1/step)))
		{
			MoveToEx(hdc, i, o_y-0.1/step, 0);
			LineTo(hdc, i, o_y + 0.1 / step);
			int x = 1 * step * (i - o_x);
			char out[10];
			_itoa(x, out, 10);
			wchar_t w_out[12];
			mbstowcs(w_out, out, 12);
			TextOut(hdc, i, o_y - 0.3 / step, w_out, strlen(out));
		}
	}
	EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit;
	static HWND hButtonPaint;
	static HWND hButtonMR;
	static HWND hButtonML;
	static HWND hButtonUp;
	static HWND hButtonDown;
	static RECT rect;
	static int width, height;
	int fLen = 0;
	static bool IsPush = 0;
	static int o_x, o_y;


	switch (message)
	{

	case WM_CREATE:
		GetWindowRect(hwnd, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
		o_x = width / 2;
		o_y = 5 * height / 8;
		hButtonPaint = CreateWindow(TEXT("button"), TEXT("paint"), WS_CHILD | WS_VISIBLE |BS_PUSHBUTTON, width/100, height/8, 50, height/32, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hEdit=CreateWindow(TEXT("edit"), TEXT("Please enter function"), WS_CHILD | WS_VISIBLE| WS_BORDER,width / 100, height / 16, width/2, height / 32,hwnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hButtonMR = CreateWindow(TEXT("button"), TEXT("R"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 80*width / 100, height / 8, 50, height / 32, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hButtonML = CreateWindow(TEXT("button"), TEXT("L"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 60*width / 100, height / 8, 50, height / 32, hwnd, (HMENU)3, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hButtonUp = CreateWindow(TEXT("button"), TEXT("Up"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 70 * width / 100, height / 16, 50, height / 32, hwnd, (HMENU)4, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hButtonDown = CreateWindow(TEXT("button"), TEXT("Down"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 70 * width / 100, 3*height / 16, 50, height / 32, hwnd, (HMENU)5, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1:
			fLen = GetWindowText(hEdit, func, sizeof(func));
			if (!fLen)
				break;
			
			func[fLen] = 0;
			wcstombs(f, func, fLen + 1);
			if (!Check(f))
			{
				SetWindowText(hEdit, TEXT("INPUT ERROR"));
				break;
			}
			IsPush = 1;
			o_x = width / 2;
			o_y = 5 * height / 8;
			InvalidateRect(hwnd, NULL, true);
			break;

		case 2:
			o_x -= width / 4;
			IsPush = 1;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 3:
			o_x += width / 4;
			IsPush = 1;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 4:
			o_y += height / 4;
			IsPush = 1;
			InvalidateRect(hwnd, NULL, true);
			break;
		case 5:
			o_y -= height / 4;
			IsPush = 1;
			InvalidateRect(hwnd, NULL, true);
			break;
		default:
			break;
		}
		return 0;
	case WM_SIZE:
	{
		GetWindowRect(hwnd, &rect);
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
		
		InvalidateRect(hwnd, NULL, true);
		return 0;
	}
	case WM_PAINT:
		UpdateWindow(hButtonPaint);
		UpdateWindow(hEdit);
		UpdateWindow(hButtonMR);
		UpdateWindow(hButtonML);
		UpdateWindow(hButtonUp);
		UpdateWindow(hButtonDown);
		if (IsPush)
		{
			DrawFunc(hwnd,o_x, o_y, 0.01, f);
			IsPush = 0;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
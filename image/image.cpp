// image.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "image.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名



using std::bitset;
FILE* fp = NULL;
int head_size = 0;
int height;
int width;
int bitcount;
bitset<16> buf2;//存储2字节的信息
bitset<32> buf4;//存储4字节的信息 

RGB_point* image_rgb;
RGBA_point* image_rgba;
int have_a = 0;

int p = 0;
HDC mDC;





// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


void ShowImage(HDC DC, RGB_point* image,int width,int height,RECT rect);
void ShowImageA(HDC DC, RGBA_point* image, int width, int height, RECT rect);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{


    errno_t err = fopen_s(&fp, "1.bmp", "rb");
    if (fp == NULL)
    {
        MessageBox(NULL, TEXT("文件打开失败!"), TEXT("error"), MB_OK);
        exit(err);
    }
    else
    {
        fread(&buf2, 2, 1, fp);
    }

    if (buf2.to_ulong() != 19778)
    {
        MessageBox(NULL, TEXT("文件格式错误!"), TEXT("error"), MB_OK);
        exit(1);
    }

    for (int i = 0; i < 4; i++)
    {
        if (fp != NULL)
        {
            fread(&buf4, 1, 4, fp);
        }
    }

    fread(&buf4, 4, 1, fp);//读取宽度
    width = buf4.to_ulong();
    fread(&buf4, 4, 1, fp);//读取高度
    height = buf4.to_ulong();


    for (int i = 0; i < 2; i++)
    {
        fread(&buf2, 2, 1, fp);
    }
    bitcount = buf2.to_ulong();//图像位数

    for (int i = 0; i < 6; i++)
    {
        fread(&buf4, 4, 1, fp);
    }

   
    
    int byteNum = (width * 24 / 32) * 4 + 4;
    image_rgb = (RGB_point*)malloc(static_cast<size_t>(width * height) * sizeof(RGB_point));
    image_rgba = (RGBA_point*)malloc(static_cast<size_t>(width * height) * sizeof(RGBA_point));

    if (bitcount / 8 == 3)
        have_a = 0;
    else if (bitcount / 8 == 4)
        have_a = 1;
    else
    {
        MessageBox(NULL, TEXT("图片位数错误!"), TEXT("error"), MB_OK);
        exit(1);
    }

    if (!have_a)
    {
        char buf = 0;
        int i = 0;
        int j = 0;
        while (i < byteNum * height)
        {
            if (i % byteNum < width * 3)
            {
                fread(&image_rgb[j].r, 1, 1, fp);
                fread(&image_rgb[j].g, 1, 1, fp);
                fread(&image_rgb[j].b, 1, 1, fp);
                i += 3;
                j++;
            }
            else
            {
                fread(&buf, 1, 1, fp);
                i += 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < width * height; i++)
        {
            fread(&image_rgba[i].r, 1, 1, fp);
            fread(&image_rgba[i].g, 1, 1, fp);
            fread(&image_rgba[i].b, 1, 1, fp);
            fread(&image_rgba[i].a, 1, 1, fp);
        }
    }
    fclose(fp);


    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_IMAGE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IMAGE));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IMAGE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    
    switch (message)
    {

    case WM_CREATE:
        SetWindowPos(hWnd, 0, 0, 0, width, height, 0);
    
    case WM_PAINT:
        {     
            PAINTSTRUCT ps;
            HDC hdc= BeginPaint(hWnd, &ps);

            if (!p)
            {
                mDC = CreateCompatibleDC(hdc);
                HBITMAP hPreBitmap = CreateCompatibleBitmap(hdc, width, height);
                HBITMAP hOldBitmap = (HBITMAP)SelectObject(mDC, hPreBitmap);
                RECT rect;
                GetClientRect(hWnd, &rect);
                if (!have_a)
                    ShowImage(mDC, image_rgb, width, height, rect);
                else
                    ShowImageA(mDC, image_rgba, width, height, rect);
                p += 1;
            }
           
            BitBlt(hdc, 0, 0, width, height, mDC, 0, 0, SRCCOPY);
            /*SelectObject(mDC, hOldBitmap);
            DeleteDC(mDC);*/

            EndPaint(hWnd, &ps);
            
        }
        break;
    case WM_DESTROY:
        free(image_rgb);
        free(image_rgba);       
        PostQuitMessage(0);
        
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void ShowImage(HDC DC, RGB_point* image, int width, int height,RECT rect)
{
    
    for (unsigned long i = 0; i < static_cast<size_t>(width * height); i++)
    {
        COLORREF color;
        color = RGB(image[i].b.to_ulong(), image[i].g.to_ulong(), image[i].r.to_ulong());
        
        int x = i % width ;
        int y = rect.bottom - i / width;

        SetPixel(DC, x, y, color);

    }
}

void ShowImageA(HDC DC, RGBA_point* image, int width, int height, RECT rect)
{
    for (unsigned long i = 0; i < static_cast<size_t>(width * height); i++)
    {
        COLORREF color;
        color = RGB(image[i].b.to_ulong(), image[i].g.to_ulong(), image[i].r.to_ulong());

        int x = i % width;
        int y = rect.bottom - i / width;

        SetPixel(DC, x, y, color);

    }
}


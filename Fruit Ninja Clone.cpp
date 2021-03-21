// Fruit Ninja Clone.cpp : Defines the entry point for the application.
//
#pragma once
#include "framework.h"
#include "Fruit Ninja Clone.h"
#include "resource.h"
#include <vector>
#include <time.h>
//#include <Windows.h>
#include <Windowsx.h>
#include <sstream>
#include <list>

#define MAX_LOADSTRING 100
#define clientHeight 6*50 //300
#define clientWidth  8*50 //400
#define GameStart 69
#define MaxCircles 5*4 //we multiply by 4 because each has the potential to be divided into 4 different circles
#define MAXSCORE 100
#define progressUpdateTimer 103
#define MaxTrail 10
#define TIMELIMITms  30000

//Structs
struct RGBCol
{
    int red;
    int green;
    int blue;
};
struct Circle
{
    int xcenter;
    int ycenter;
    int radius;
    int xvel;
    int yvel;
    RGBCol color;
};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
int boardSizeH = 6;
int boardSizeW = 8;
bool settingNewGame = false;
bool gameOver = false;
bool overlaySet = true;
int start = GetTickCount64();
int SCORE = 0;
bool MouseMoving = false;
//bool continueMouseTracking = false;
std::vector<Circle> CircleStore;
std::vector<Circle> tempStore;
std::list<POINT>TrailStore;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM MyRegisterWhiteSquareClass(HINSTANCE hInstance);
ATOM MyRegisterBlackSquareClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    WndProcSquare(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void NewGame(HWND hWnd);
void CircleGenerator(HDC* Memhdc, HBITMAP* Membitmap, HWND hWnd);
void gameOverscreen(HDC* Memhdc, HWND hWnd);
//void TrailManager(HWND hWnd);
void TrailManager(HDC* Memhdc, HBITMAP* Membitmap, HWND hWnd);
//void progressUpdater(HWND hWnd);


//

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    srand(time(NULL));
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FRUITNINJACLONE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    MyRegisterWhiteSquareClass(hInstance);
    MyRegisterBlackSquareClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FRUITNINJACLONE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRUITNINJACLONE));
    wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FRUITNINJACLONE);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

ATOM MyRegisterWhiteSquareClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProcSquare;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRUITNINJACLONE));
    wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
    wcex.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FRUITNINJACLONE);
    wcex.lpszClassName = L"WhiteSquareClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_FRUITNINJACLONE));
    return RegisterClassExW(&wcex);
}
ATOM MyRegisterBlackSquareClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProcSquare;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FRUITNINJACLONE));
    wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
    wcex.hbrBackground = (HBRUSH)(GetStockObject(BLACK_BRUSH));
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FRUITNINJACLONE);
    wcex.lpszClassName = L"BlackSquareClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_FRUITNINJACLONE));
    return RegisterClassExW(&wcex);
}
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable
    RECT rDesk;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rDesk, 0);
    //static int height = (rc.bottom - rc.top);
    //static int width = (rc.right - rc.left);
    static int centerX = (-rDesk.left + rDesk.right + 1) / 2;
    static int centerY = (-rDesk.top + rDesk.bottom + 1) / 2;
    //SetWindowPos(hWnd, HWND_TOPMOST, centerX - 300 / 2, centerY - 400 / 2, 400, 300,SWP_NOREPOSITION);
   /* GetClientRect(hWnd, &rc);
    MoveWindow(hWnd, centerX - (300 + (rc.right - width) / 2), centerY - (400 + (rc.right - width / 2)), 400, 300, TRUE);*/
    RECT rc = { 0,0,clientWidth,clientHeight }; //order: bottom,left,right,top. Exactly as the autocomplete suggested on typing rc. (the order of non-star elements)
    //rc.bottom = centerY + clientHeight / 2;
    //rc.left = centerX - clientWidth / 2;
    //rc.right = centerX + clientWidth / 2;
    //rc.top = centerY - clientHeight / 2;

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_THICKFRAME, TRUE);
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_THICKFRAME | WS_VISIBLE,
        centerX - clientWidth / 2, centerY - clientHeight / 2, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance, nullptr);


    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    HMENU menu; menu = GetMenu(hWnd);
    CheckMenuItem(menu, ID_BOARD_SMALL, MF_CHECKED);
    LPWSTR size = new WCHAR(100);
    GetPrivateProfileStringW(L"Board", L"Size", L"SMALL", size, 100, L"./boardConfig.ini");
    if (GetLastError() != 0x2)
    {
        if (wcscmp(size, L"SMALL") == 0)
        {
            SendMessage(hWnd, WM_COMMAND, ID_BOARD_SMALL, 0);
        }
        if (wcscmp(size, L"MEDIUM") == 0)
        {
            SendMessage(hWnd, WM_COMMAND, ID_BOARD_MEDIUM, 0);
        }
        if (wcscmp(size, L"BIG") == 0)
        {
            SendMessage(hWnd, WM_COMMAND, ID_BOARD_BIG, 0);
        }
    }
    NewGame(hWnd);
    //const int rows = 6;
    //const int columns = 8;
    //HWND boardhWnd[rows][columns];
    //for (int i = 0; i < rows; i++)
    //{
    //    for (int j = 0; j < columns; j++)
    //    {
    //        if ((i+j) % 2 != 0)  //row and column both even or both odd => white & one of them even and other odd =>black
    //        {
    //            boardhWnd[i][j] = CreateWindow(L"WhiteSquareClass", 0, WS_VISIBLE | WS_CHILDWINDOW, j * 50, i * 50, 50, 50, hWnd, NULL, hInstance, NULL);
    //        }
    //        else 
    //        {
    //            boardhWnd[i][j] = CreateWindow(L"BlackSquareClass", 0, WS_VISIBLE|WS_CHILDWINDOW, j * 50, i * 50, 50, 50, hWnd, NULL, hInstance, NULL);
    //        }
    //    }
    //}

    //for (int i = 0; i < rows; i++)
    //{
    //    for (int j = 0; j < columns; j++)
    //    {
    //        ShowWindow(boardhWnd[i][j], nCmdShow);
    //        UpdateWindow(boardhWnd[i][j]);
    //    }
    //}

    //for (int i = 0; i < rows; i++)
    //{
    //    for (int j = 0; j < columns; j++)
    //    {
    //        boardhWnd[count] = CreateWindow(szWindowClass, nullptr,WS_CHILD&~WS_SYSMENU,j *50, i * 50, 50,50,NULL, NULL, hInst, NULL);
    //        ShowWindow(boardhWnd[count], SW_SHOWNOACTIVATE);
    //        SetWindowPos(boardhWnd[count],HWND_TOPMOST,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
    //        if ((i + 1) % 2 == 0)//i is even
    //        {
    //            if ((j + 1) % 2 == 0)
    //            {
    //                //fill black
    //            }
    //            else
    //            {
    //                //keep white
    //            }
    //        }
    //        else
    //        {
    //            if ((j + 1) % 2 == 0)
    //            {
    //                //keep white
    //            }
    //            else
    //            {
    //                //fill black
    //            }
    //        }
    //        count++;
    //    }
    //}


    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rc;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
    //static int height = (rc.bottom - rc.top);
    //static int width = (rc.right - rc.left);
    const int centerX = (rc.right - rc.left + 1) / 2;
    const int centerY = (rc.bottom - rc.top + 1) / 2;
//    int gameTimer = NULL;
    switch (message)
    {

    case WM_CREATE:
    {    //GetWindowRect(hWnd, &rc);
        //const int cx = GetSystemMetrics(SM_CXBORDER);
        //const int cy = GetSystemMetrics(SM_CYBORDER
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        NewGame(hWnd);
        SetTimer(hWnd, GameStart, 33.33, 0); //gameTimer = SetTimer(hWnd, GameStart, 33.33, 0);
        //        SetTimer()
                //rc.left = centerX - clientWidth / 2;
                //rc.top = centerY - clientHeight / 2;
                //rc.right = centerX + clientWidth / 2;
                //rc.bottom = centerY + clientHeight / 2;
                //SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                //MoveWindow(hWnd, centerX - clientWidth / 4, centerY - clientHeight / 4, clientWidth, clientHeight, TRUE);
                //MoveWindow(hWnd, centerX - 400 / 2, centerY - 300 / 2, 400, 300, TRUE);
    }
    break;

    //case WM_GETMINMAXINFO:
    //{
    //    MINMAXINFO* minMaxInfo = (MINMAXINFO*)lParam;
    //    minMaxInfo->ptMaxSize.x = minMaxInfo->ptMaxTrackSize.x = 1920;
    //    minMaxInfo->ptMaxSize.y = minMaxInfo->ptMaxTrackSize.y = 1080;
    //}
    //break;
    case WM_WINDOWPOSCHANGING:
    {
        //RECT* rcpos = (RECT*)lParam;
        //rcpos->left = centerX - clientWidth / 2;
        //rcpos->top = centerY - clientHeight / 2;
        SetWindowPos(hWnd, HWND_TOPMOST, centerX-clientWidth/2, centerY-clientHeight/2, 0, 0,SWP_NOMOVE|SWP_NOSIZE);

        if (!settingNewGame)
        {
            WINDOWPOS* pos = (WINDOWPOS*)lParam;
            GetWindowRect(hWnd, &rc);
            pos->y = rc.top; //centerX-clientHeight/2
            pos->x = rc.left;
        }
        //        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
                //pos->y = centerX - clientHeight / 2;
                //pos->x = centerY - clientWidth / 2;
    }
    break;
    //case WM_SIZING:
    //{
    //    GetWindowRect(hWnd, &rc);
    //    MoveWindow(hWnd, centerX - width / 4, centerY - height / 4, width / 2, height / 2, TRUE);
    //    break;
    //}
    case WM_MOUSEMOVE:
    {
        if (!gameOver)
        {
            SetLayeredWindowAttributes(hWnd, 0, (255 * 100) / 100, LWA_ALPHA);  //Fully opaque
            UpdateWindow(hWnd);
        }
        MouseMoving = TRUE;
//        TrailManager(hWnd);
        std::vector<Circle> tempStore;
        for (std::vector<Circle>::iterator cir = std::begin(CircleStore); cir != std::end(CircleStore); )
        {
            POINT p = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
//            (x - center_x) ^ 2 + (y - center_y) ^ 2 < radius ^ 2
//            int hypotenuse = sqrt((p.x-cir->xcenter) * (p.x-cir->xcenter) + (p.y - cir->ycenter) * (p.y - cir->ycenter)); //so that we can compare it to radius
//            if (hypotenuse < cir->radius&&!settingNewGame)
            if(cir->radius>sqrt((p.x-cir->xcenter)*(p.x - cir->xcenter) +(p.y-cir->ycenter)*(p.y - cir->ycenter)))
            {
                //int xcenter;
                //int ycenter;
                //int radius;
                //int xvel;
                //int yvel;
                //RGBCol color;
                Circle c1 = { cir->xcenter - cir->radius / 2,cir->ycenter - cir->radius / 2,cir->radius/2,rand() % 5,-abs(rand() % 5) - 5,cir->color };    //c1 c2
                Circle c2 = { cir->xcenter + cir->radius / 2,cir->ycenter - cir->radius / 2,cir->radius/2,rand() % 5,-abs(rand() % 5) - 5,cir->color };   //c3 c4
                Circle c3 = { cir->xcenter - cir->radius / 2,cir->ycenter + cir->radius / 2,cir->radius/2,rand() % 5,-abs(rand() % 5) - 5,cir->color };
                Circle c4 = { cir->xcenter + cir->radius / 2,cir->ycenter + cir->radius / 2,cir->radius / 2,rand() % 5,-abs(rand() % 5) - 5,cir->color };
//                cir->color = c4.color; cir->xcenter = c4.xcenter; cir->ycenter = c4.ycenter; cir->radius = c4.radius; cir->xvel = c4.xvel; cir->yvel = c4.yvel;
                tempStore.push_back(c1); tempStore.push_back(c2); tempStore.push_back(c3); tempStore.push_back(c4);
                cir = CircleStore.erase(cir);
                if (!settingNewGame)
                {
                    SCORE += 1;
                }
                break;
            }
            else
            {
                cir++;
            }
        }
        for (std::vector<Circle>::iterator tcir = std::begin(tempStore); tcir != std::end(tempStore);)
        {
            CircleStore.push_back(*tcir);
            tcir = tempStore.erase(tcir);
        }   
    }
    break;
    case WM_NCMOUSEMOVE:
    {
        MouseMoving = FALSE;
        SetTimer(hWnd, 1, 3000, NULL);
    }
    break;
    case WM_TIMER:
    {
        if (wParam == 1)
        {
            SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
            if (!gameOver)
            {
                SetLayeredWindowAttributes(hWnd, 0, (255 * 90) / 100, LWA_ALPHA);   //90% opacity
                UpdateWindow(hWnd);
            }

        }
        else if (wParam == GameStart)
        {
//            CircleGenerator(hWnd);
            GetClientRect(hWnd,&rc);
//            InvalidateRect(hWnd, &rc, FALSE);
            SendMessage(hWnd, WM_PAINT, 0, 0);
        }
        else if (wParam == 102)
        {
            if (!gameOver)
            {
                gameOver = TRUE;
//                CircleGenerator(hWnd);
                SendMessage(hWnd, WM_PAINT, 0,0);
//                gameOverscreen(hWnd);
            }
        }
        else if (wParam == progressUpdateTimer)
        {
            //progressUpdater(hWnd);
        }
    }
    break;
    case WM_COMMAND:
    {
        //HMENU menu = GetMenu(hWnd);
        //CheckMenuItem(menu, ID_BOARD_SMALL, MF_UNCHECKED);
        //CheckMenuItem(menu, ID_BOARD_MEDIUM, MF_UNCHECKED);
        //CheckMenuItem(menu, ID_BOARD_BIG, MF_UNCHECKED);
        int wmId = LOWORD(wParam);
        HMENU menu = GetMenu(hWnd);
        if (wmId == ID_BOARD_SMALL || wmId == ID_BOARD_MEDIUM || wmId==ID_BOARD_BIG)
        {
            CheckMenuItem(menu, ID_BOARD_SMALL, MF_UNCHECKED);
            CheckMenuItem(menu, ID_BOARD_MEDIUM, MF_UNCHECKED);
            CheckMenuItem(menu, ID_BOARD_BIG, MF_UNCHECKED);
        }
        // Parse the menu selections:
        switch (wmId)
        {
        case ID_GAME_NEWGAME:
        {
           // KillTimer(hWnd, gameTimer);
            NewGame(hWnd);
        }
        break;
        case ID_BOARD_SMALL:
        {
            boardSizeH = 6;
            boardSizeW = 8;
            CheckMenuItem(menu, ID_BOARD_SMALL, MF_CHECKED);
            WritePrivateProfileString(L"Board", L"Size", L"SMALL", L"./boardConfig.ini");
            //KillTimer(hWnd, gameTimer);
            NewGame(hWnd);
        }
        break;
        case ID_BOARD_MEDIUM:
        {
            boardSizeH = 10;
            boardSizeW = 12;
            CheckMenuItem(menu, ID_BOARD_MEDIUM, MF_CHECKED);
            WritePrivateProfileString(L"Board", L"Size", L"MEDIUM", L"./boardConfig.ini");
            //KillTimer(hWnd, gameTimer);
            NewGame(hWnd);
        }
        break;
        case ID_BOARD_BIG:
        {
            boardSizeH = 12;
            boardSizeW = 16;
            CheckMenuItem(menu, ID_BOARD_BIG, MF_CHECKED);
            WritePrivateProfileString(L"Board", L"Size", L"BIG", L"./boardConfig.ini");
            //KillTimer(hWnd, gameTimer);
            NewGame(hWnd);
        }
        break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        DeleteObject(menu); //should I even have this? :O
    }
    break;
    case WM_PAINT:
    {
        if (!overlaySet)
        {
            RECT Client_Rect;
            GetClientRect(hWnd, &Client_Rect);
            int win_width = Client_Rect.right - Client_Rect.left;
            int win_height = Client_Rect.bottom + Client_Rect.left;

            //    PAINTSTRUCT ps;
            HDC Memhdc;
            HDC hdc;
            hdc = GetDC(hWnd);  //BeginPaint(hWnd, &ps);
            Memhdc = CreateCompatibleDC(hdc);
            HBITMAP Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
            SelectObject(Memhdc, Membitmap);
            CircleGenerator(&Memhdc, &Membitmap, hWnd);
            if (MouseMoving)
            {
                TrailManager(&Memhdc, &Membitmap, hWnd);
            }
            else
            {
                while (TrailStore.size() != 0)
                {
                    TrailStore.pop_front();
                }
            }
            BitBlt(hdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);
            DeleteDC(Memhdc);
            ReleaseDC(hWnd, hdc);
            //    EndPaint(hWnd, &ps);




            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            //if (!settingNewGame)
            //{
            //    
            //}
            //DeleteDC(hdc);
            //EndPaint(hWnd, &ps);
            //if (!settingNewGame)
            //{
            //    RECT Client_Rect;
            //    GetClientRect(hWnd, &Client_Rect);
            //    int win_width = Client_Rect.right - Client_Rect.left;
            //    int win_height = Client_Rect.bottom + Client_Rect.left;
            //    HDC hdc;
            //    HDC Memhdc;
            //    HBITMAP Membitmap;
            //    hdc = GetDC(hWnd);  //BeginPaint(hWnd, &ps);
            //    Memhdc = CreateCompatibleDC(hdc);
            //    Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
            //    SelectObject(Memhdc, Membitmap);
            //    HBRUSH brush = CreateSolidBrush(RGB(64, 128, 0));
            //    SelectObject(Memhdc, brush);
            //    Rectangle(Memhdc,  0, win_height-20, win_width*(SCORE/MAXSCORE)*100, win_height);
            //    DeleteObject(brush);
            //    BitBlt(hdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);
            //    DeleteObject(Membitmap);
            //    DeleteDC(Memhdc);
            //    ReleaseDC(hWnd, hdc);
            //}
            return DefWindowProc(hWnd, WM_PAINT, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK WndProcSquare(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void NewGame(HWND hWnd)
{
    start = GetTickCount64();
    SCORE = 0;
    gameOver = FALSE; overlaySet = FALSE;
    //int boardSizeH;
    //int boardSizeW;
    //HMENU menu = GetMenu(hWnd);
    //MENUITEMINFO* mItem = new MENUITEMINFO;
    //GetMenuItemInfoW(menu, ID_BOARD_SMALL, FALSE, mItem); mItem->fMask = MIIM_STATE; mItem->dwTypeData = NULL;
    //long a = mItem->fState & MFS_CHECKED;
    //if ((mItem->fState|MFS_CHECKED)==mItem->fState)
    //{
    //    boardSizeH = 6;
    //    boardSizeW = 8;
    //}
    //else
    //{
    //    GetMenuItemInfoW(menu, ID_BOARD_MEDIUM, TRUE, mItem); mItem->fMask = MIIM_STATE; mItem->dwTypeData = NULL;
    //    if (mItem->fState == MFS_CHECKED)
    //    {
    //        boardSizeH = 10;
    //        boardSizeW = 12;
    //    }
    //    else
    //    {
    //        GetMenuItemInfoW(menu, ID_BOARD_BIG, TRUE, mItem); mItem->fMask = MIIM_STATE; mItem->dwTypeData = NULL;
    //        if (mItem->fState == MFS_CHECKED)
    //        {
    //            boardSizeH = 12;
    //            boardSizeW = 16;
    //        }
    //    }
    //}
    //delete mItem;


    //Deleting current circles:
   // continueMouseTracking = false; //Notifies WM_CHANGING that the previous circles are invalid now.
    for (std::vector<Circle>::iterator cir = std::begin(CircleStore); (cir != std::end(CircleStore)) && (!CircleStore.empty()); )
    {
        cir = CircleStore.erase(cir);
    }
    //Setting Up:
    SCORE = 0;
    RECT rc;
    settingNewGame = true;  //Stops WM_POSCHANING from preventing Window position change.
    //Cleaning old board
    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255)); //create brush
    HDC hdc = GetDC(hWnd);
    SelectObject(hdc, brush); //select brush into DC
    Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)); //draw rectangle over whole screen
    GetWindowRect(hWnd, &rc);
    DeleteObject(brush);
    ReleaseDC(hWnd, hdc);        //we use ReleaseDC for DCs gotten via GetDC, for CreateDC use DeleteDC instead
    //Sizing board:
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
    int centerX = (rc.right - rc.left + 1) / 2;
    int centerY = (rc.bottom - rc.top + 1) / 2;
    int clientH = boardSizeH * 50;
    int clientW = boardSizeW * 50;
    rc = { 0,0,clientW,clientH };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_THICKFRAME, TRUE);
    //MoveWindow(hWnd, centerX - clientW / 2, centerY - clientH / 2, rc.right - rc.left, rc.bottom - rc.top, FALSE);
    SetWindowPos(hWnd, HWND_TOPMOST, centerX - clientW / 2, centerY - clientH / 2, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW);
    //Drawing board
    for (int i = 0; i < boardSizeH; i++)
    {
        for (int j = 0; j < boardSizeW; j++)
        {
            hdc = GetDC(hWnd);
            if ((i + j) % 2 != 0)  //row and column both even or both odd => white & one of them even and other odd =>black
            {

                //               HBRUSH hbrush=(HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));
                HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
                SelectObject(hdc, brush);

                //               SelectObject(hdc, GetStockObject(DC_BRUSH));
               //                SetDCBrushColor(hdc, RGB(255, 255, 255));
                Rectangle(hdc, j * 50, i * 50, j * 50 + 50, i * 50 + 50);
                DeleteObject(brush);


            }
            else
            {
                HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
                SelectObject(hdc, brush);
                //SelectObject(hdc, GetStockObject(DC_BRUSH));
                //SetDCBrushColor(hdc, RGB(0,0,0));
                Rectangle(hdc, j * 50, i * 50, j * 50 + 50, i * 50 + 50);
                DeleteObject(brush);
            }
            ReleaseDC(hWnd, hdc);
        }
    }


    settingNewGame = false;
    SetTimer(hWnd, 102, TIMELIMITms,0);
    SetTimer(hWnd, progressUpdateTimer, 1, 0);
}


//


void CircleGenerator(HDC* Memhdc, HBITMAP* Membitmap, HWND hWnd)
{
    RECT Client_Rect;
    GetClientRect(hWnd, &Client_Rect);
    int win_width = Client_Rect.right - Client_Rect.left;
    int win_height = Client_Rect.bottom + Client_Rect.left;
    if (!gameOver || !overlaySet)
    {


        //Circle Generation 
        if (CircleStore.size() < MaxCircles / 4) //we divide maxsize by 4 because each ball can be divided into 4 sperate ones
        {
            RGBCol col = { abs(rand() % 225 + 15),abs(rand() % 225 + 15),abs(rand() % 225 + 15) };   //225+15 not 255 because I want to avoid fully black and fully white circles to avoid confusion with background
            Circle cir = { abs(rand() % win_width) + 20,win_height,abs(rand() % 20 + 15), rand() % 5, -abs(rand() % 5) - 5,col };
            cir.ycenter += cir.radius;
            CircleStore.push_back(cir);
        }
        for (std::vector<Circle>::iterator cir = std::begin(CircleStore); cir != std::end(CircleStore); )
        {

            cir->xcenter += cir->xvel;
            cir->ycenter += cir->yvel;
            if ((cir->ycenter + cir->radius) <= 0 || (cir->xcenter + cir->radius) <= 0 || (cir->xcenter - cir->radius) >= win_width) //checks if whole circle is out of bounds
            {
                cir = CircleStore.erase(cir);
            }
            else
            {
                cir++;
            }
        }
        //Board drawing:
        for (int i = 0; i < boardSizeH; i++)
        {
            for (int j = 0; j < boardSizeW; j++)
            {
                if ((i + j == 0))
                {

                }
                if ((i + j) % 2 != 0)  //row and column both even or both odd => white & one of them even and other odd =>black
                {

                    //               HBRUSH hbrush=(HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));
                    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
                    SelectObject(*Memhdc, brush);

                    //               SelectObject(hdc, GetStockObject(DC_BRUSH));
                   //                SetDCBrushColor(hdc, RGB(255, 255, 255));
                    Rectangle(*Memhdc, j * 50, i * 50, j * 50 + 50, i * 50 + 50);
                    DeleteObject(brush);
                }
                else
                {
                    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
                    SelectObject(*Memhdc, brush);
                    //SelectObject(hdc, GetStockObject(DC_BRUSH));
                    //SetDCBrushColor(hdc, RGB(0,0,0));
                    Rectangle(*Memhdc, j * 50, i * 50, j * 50 + 50, i * 50 + 50);
                    DeleteObject(brush);
                }
            }
        }
        //drawing circles begins
        for (std::vector<Circle>::iterator cir = std::begin(CircleStore); cir != std::end(CircleStore); cir++)
        {
            HBRUSH brush = CreateSolidBrush(RGB(cir->color.red, cir->color.green, cir->color.blue));
            SelectObject(*Memhdc, brush);
            RECT temp = { cir->xcenter - cir->radius,cir->ycenter - cir->radius,cir->xcenter + cir->radius,cir->ycenter + cir->radius };
            Ellipse(*Memhdc, temp.left, temp.top, temp.right, temp.bottom);
            DeleteObject(brush);
        }
        //drawing circles ends

        //drawing score:
        if (SCORE > MAXSCORE)
        {
            SCORE = MAXSCORE;
        }
        std::wstringstream wstrstrm;
        std::wstring wstr;
        wstrstrm << SCORE;
        wstrstrm >> wstr;
        HFONT hfOld = CreateFont(40, 0, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, NULL);
        SelectObject(*Memhdc, hfOld);
        LPCWSTR scoreWstr = wstr.c_str();
        SetBkMode(*Memhdc, TRANSPARENT);
        SetTextColor(*Memhdc, RGB(64, 128, 0));
        RECT r = { win_width - 50, 0,win_width,50 };
        DrawText(*Memhdc, scoreWstr, wstr.size(), &r, DT_RIGHT | DT_TOP);
        SetBkMode(*Memhdc, OPAQUE);
        SetTextColor(*Memhdc, RGB(0, 0, 0));
        DeleteFont(hfOld);
        //Drawing score ends
//        Drawing progress begins:
        HBRUSH brush = CreateSolidBrush(RGB(64, 128, 0));
        SelectObject(*Memhdc, brush);
        //        int progress = win_width/TIMELIMITms.0 * ((float)SCORE / MAXSCORE);
        double progress = (win_width / (double)TIMELIMITms) * (GetTickCount64() - start);
        Rectangle(*Memhdc, 0, win_height - 20, progress, win_height);
        DeleteObject(brush);
        //        Drawing progress ends

         //       Drawing Game Over Screen
        //        if (SCORE >= MAXSCORE)
        if (SCORE >= MAXSCORE || (gameOver && !overlaySet))
        {
//            SCORE = MAXSCORE;
            gameOver = TRUE;
            SetLayeredWindowAttributes(hWnd, 0, (255 * 100) / 100, LWA_ALPHA);
            gameOverscreen(Memhdc, hWnd);
            overlaySet = TRUE;
        }
        //Drawing GameOver Ends
    }
}

void gameOverscreen(HDC*Memhdc,HWND hWnd)
{
    RECT Client_Rect;
    GetClientRect(hWnd, &Client_Rect);
    int win_width = Client_Rect.right - Client_Rect.left;
    int win_height = Client_Rect.bottom + Client_Rect.left;
//

    HDC MemhdcOverlay = CreateCompatibleDC(*Memhdc);
    HBITMAP MembitmapOverlay = CreateCompatibleBitmap(*Memhdc, win_width, win_height);
    SelectObject(MemhdcOverlay, MembitmapOverlay);
    HBRUSH brush = CreateSolidBrush(RGB(64, 182, 0));
    SelectObject(MemhdcOverlay, brush);
    Rectangle(MemhdcOverlay, 0, 0, win_width, win_height);
        //
    BLENDFUNCTION blend;
    blend.BlendOp = AC_SRC_OVER;
    blend.BlendFlags = 0;
    blend.SourceConstantAlpha = (255 * 50) / 100;
    blend.AlphaFormat = 0;
    DeleteObject(brush);
    GdiAlphaBlend(*Memhdc, 0, 0, win_width, win_height, MemhdcOverlay, 0, 0, win_width, win_height, blend);
    //
    DeleteObject(MembitmapOverlay);
    DeleteDC(MemhdcOverlay);
}

void TrailManager(HDC* Memhdc, HBITMAP* Membitmap, HWND hWnd)
{
    if (!overlaySet&&!gameOver)
    {
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ScreenToClient(hWnd, &cursorPos);
        TrailStore.push_back(cursorPos);
        if (TrailStore.size() > MaxTrail)
        {
            TrailStore.pop_front();
        }

        POINT trl[MaxTrail];
        int trailsread = min(MaxTrail, TrailStore.size());
        std::list<POINT>::const_iterator it = TrailStore.begin();
        for (int i = 0; i < trailsread; i++)
        {
            trl[i] = *it++;
        }

        RECT Client_Rect;
        GetClientRect(hWnd, &Client_Rect);
        int win_width = Client_Rect.right - Client_Rect.left;
        int win_height = Client_Rect.bottom + Client_Rect.left;
        HPEN trailpen = CreatePen(PS_SOLID, 3, RGB(255, 100, 50));
//        Membitmap = CreateCompatibleBitmap(*Memhdc, win_width, win_height);
        SelectObject(*Memhdc, *Membitmap);
        SelectObject(*Memhdc, trailpen);
//        SetBkMode(Memhdc, TRANSPARENT);
        Polyline(*Memhdc, trl, trailsread);
        DeleteObject(trailpen);
    }
}

//void progressUpdater(HWND hWnd)
//{
//    RECT Client_Rect;
//    GetClientRect(hWnd, &Client_Rect);
//    int win_width = Client_Rect.right - Client_Rect.left;
//    int win_height = Client_Rect.bottom + Client_Rect.left;
//    HBRUSH brush = CreateSolidBrush(RGB(64, 128, 0));
//    HDC Memhdc;
//    HDC hdc;
//    HBITMAP Membitmap;
//    hdc = GetDC(hWnd);  //BeginPaint(hWnd, &ps);
//    Memhdc = CreateCompatibleDC(hdc);
//    Membitmap = CreateCompatibleBitmap(hdc, win_width, win_height);
//    SelectObject(Memhdc, Membitmap);
//    SelectObject(Memhdc, brush);
//    SetBkMode(Memhdc, TRANSPARENT);
//    int progress = win_width * ((float)SCORE / MAXSCORE);
//    Rectangle(Memhdc, 0, win_height - 20, progress, win_height);
//    BitBlt(hdc, 0, 0, win_width, win_height, Memhdc, 0, 0, SRCCOPY);
//    DeleteObject(brush);
//    DeleteDC(Memhdc);
//    DeleteObject(Membitmap);
//    ReleaseDC(hWnd,hdc);
//}
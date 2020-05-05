#pragma once
//-----------------------------------------------------------------------------------------------------------------------
#define MAX_LOADSTRING 100
#define IDB_MY_BUTTON     3100


#define IDC_CLOSE 10003

#define IDC_STATE 10004

#define IDC_BUTT 78454

#define IDC_MINIMIZE 12111

#define IDC_EDIT1 114514

#define CLOSEBTN 114513

//-------------------------------------------------------------------------------------------------------------------------
#include "framework.h" //VS2019中相当于stdafx.h
#include "Resource.h"
#include <tchar.h>
#include <stdio.h>
#include <commctrl.h>
#include <sstream>
#include <atlconv.h>
//-----------------------------------------------------------------------------------------------------------------------
HINSTANCE b_hInstance;
//------------------------------------------------------------------------------------------------------------------------
int DlgClose(HWND hwndDlg, LPARAM lParam)
{
    POINT pt;
    char txt[80];
    pt.x = LOWORD(lParam);
    pt.y = HIWORD(lParam);
    sprintf_s(txt, "x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
    OutputDebugString(txt);
    RECT  rc = { 432, 15, 70, 30 };// 这是 bmp 在主窗口的位置 ！
    if (PtInRect(&rc, pt))
    {
        MessageBox(NULL, "1", "2", 0);
        return WM_CLOSE;
    }
    return -1;
}
//------------------------------------------------------------------------------------------------------------------------
HWND g_bt1;
HWND g_bt2;
WNDPROC BToldProc;

typedef struct tagBTN
{// 
    HWND hWnd;          // handle of owner window
} BTN_PARAM;
//
//
LRESULT CALLBACK BTProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    static HFONT hFont;
    PAINTSTRUCT ps;
    HDC hdc;
    HBRUSH br;
    char txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        br = CreateSolidBrush(RGB(0, 255, 0));
        FillRect(hdc, &ps.rcPaint, br);
        GetWindowText(hWnd, txt, 40);
        SetBkMode(hdc, TRANSPARENT);
        DrawText(hdc, txt, strlen(txt), &ps.rcPaint, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        EndPaint(hWnd, &ps);
        DeleteObject(br);
        break;
    }
    //
    return CallWindowProc(BToldProc, hWnd, Msg, wParam, lParam);
}
//
int CloseBTN(
    HWND hWnd          // handle of owner window
)
{
    static HFONT hFont;
    BTN_PARAM btn;
    btn.hWnd = hWnd;
    g_bt1 = CreateWindow("Button", "关闭", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,//默认按钮样式
        185, 170, 70, 30, hWnd, (HMENU)IDC_BUTT, b_hInstance, NULL);
    BToldProc = (WNDPROC)SetWindowLong(g_bt1, GWL_WNDPROC, (LONG)BTProc);
    return -1;
}
/*UIMAIN头文件 自定义对话框模块--------------------------------------------------------------------------------------------------------------
* 调用方式: TipBox(NULL,"TEXT","TITLE",0)；                                                                                             | *
* 或者:TipBox_D();                                                                                                                     | *
* 关闭按钮已自动包含:CloseBTN                                                                                                            |*
---------------------------------------------------------------------------------------------------------------------------------------*/
typedef struct tagMMB
{// 
    HWND hWnd;          // handle 

    LPCTSTR lpText;     // text 

    LPCTSTR lpCaption;  //  title 

    UINT uType;         // style 

} MMB_PARAM;
//
BOOL CALLBACK DialogProc1(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP hBitmap;                  // 1 静态变量
    static HBITMAP hBitmap2;
    static HBITMAP hBitmap3;
    static HFONT hFont;//定义静态字体变量
    BITMAP         bitmap;
    static HWND close;
    HDC hdcMem = NULL;
    static int      bmWidth, bmHeight;       // 2 静态变量
    char txt[40];
    MMB_PARAM* pmmb = (MMB_PARAM*)lParam;
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        SetWindowText(hwndDlg, pmmb->lpCaption);
        SetWindowText(GetDlgItem(hwndDlg, IDC_STATIC), pmmb->lpText);
        //222222
        CloseBTN(hwndDlg);
        return TRUE;
    case WM_PAINT:
    {
        HPEN hpen = CreatePen(PS_SOLID,2,RGB(0,122,204));
        HBRUSH br2 = CreateSolidBrush(RGB(0, 122, 204));
        HPEN hpenOld = NULL;
        HDC hdc = NULL;
        HDC hdc2 = NULL;
        PAINTSTRUCT ps;
        hdc = BeginPaint(hwndDlg, &ps);
        HBRUSH br = CreateSolidBrush(RGB(60, 60, 60));
        FillRect(hdc, &ps.rcPaint, br);
        SelectObject(hdc, hpen);
        SelectObject(hdc, br2);
        Rectangle(hdc, 0, 0, 455, 30);
        ReleaseDC(hwndDlg, hdc);//Over                                             // 12
        EndPaint(hwndDlg, &ps);
        DeleteObject(br2);
        DeleteObject(br);
        return TRUE;
    }
    case WM_SIZE: //无效但需要存在的代码
    {
        LONG_PTR Style = ::GetWindowLongPtr(hwndDlg, GWL_STYLE);
        Style = Style & ~WS_CAPTION & ~WS_SYSMENU & ~WS_SIZEBOX;
        ::SetWindowLongPtr(hwndDlg, GWL_STYLE, Style);
        return TRUE;
    }
    case WM_LBUTTONDOWN:
    {
        if (DlgClose(hwndDlg, lParam) > 0)
        {
            DeleteObject(hBitmap);
            DeleteObject(hFont);
            EndDialog(hwndDlg, 0);
            break;
        }
        // 移动窗口 
        SendMessage(hwndDlg, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_COMMAND:
    {
        case IDC_BUTT:
        {
            EndDialog(hwndDlg, 0);
        }
    }
    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
    }
    return FALSE;
}
//
int TipBox(
    HWND hWnd,          // handle 
    LPCTSTR lpText,     // text 
    LPCTSTR lpCaption,  // title 
    UINT uType          // style 
)
{
    MMB_PARAM mmb;
    mmb.hWnd = hWnd;
    mmb.lpText = lpText;
    mmb.lpCaption = lpCaption;
    mmb.uType = uType;
    DialogBoxParam((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
        MAKEINTRESOURCE(IDD_TIPBOX), NULL, DialogProc1, (LPARAM)&mmb);
    return -1;
}

#define D_TipBox TipBox
#define B_CLOSE CloseBTN
/*-----------------------------------------------------------------------------------------
struct OVER
-----------------------------------------------------------------------------------------*/

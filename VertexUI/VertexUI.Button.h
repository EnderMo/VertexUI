#pragma once
/*
* VertexUI Buttons
* 
* Code by VertexStudio-EnderMo 2020-2021
* 
* All the codes are unlimited to use.
* 
* VertexUI 2021
*/


#include "framework.h"
#include <CommCtrl.h>
#include "VertexUI.colors.h"
#pragma warning(disable:4996)

#ifdef SimpleCode
#define Button VertexUIButton
#define ButtonEx VertexUIButtonEx
#endif


namespace NormalButton{
    HINSTANCE b_hInstance;
    HWND g_bt1;
    HWND g_bt2;
    WNDPROC ButtonProc;
    WNDPROC BTold;

    typedef struct tagBTN
    {// 
        HWND hWnd;         
        BOOL x1; 
        BOOL x2; 
        LPWSTR in;
        UINT style;
    } BTN_PARAM;
    int NormalButtonHeight = 40;
    int nh = NormalButtonHeight;
    void DrawFrameBtn(HDC hdc, HPEN hpen, RECT rect, BOOL wid, COLORREF cl)
    {
        hpen = CreatePen(PS_SOLID, wid, cl);
        SelectObject(hdc, hpen);
        SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        //Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
        Rectangle(hdc, 2, 2, rect.right - rect.left-1, rect.bottom - rect.top-1);
    }
}


//
//

LRESULT CALLBACK BTProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    using namespace::NormalButton;
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    TCHAR txt[40];
    switch (Msg)
    {//
    case WM_PAINT:
    {
        HBRUSH hbr = NULL;
        HPEN hpen = 0;
        hdc = BeginPaint(hWnd,&ps);


        hbr = CreateSolidBrush(UICOLOR_BUTTON);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, UICOLOR_BUTTON_TEXT);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        //TextOut(hdc, 16, 7, txt, wcslen(txt) /*&ps.rcPaint*//*DT_SINGLELINE | DT_CENTER | DT_VCENTER*/);
        DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        DrawFrameBtn(hdc, hpen, rc, 2, UICOLOR_BUTTON);

        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
        DeleteObject(hbr);
        DeleteObject(hpen);
        EndPaint(hWnd, &ps);
        OutputDebugStringA("Button Created");
        break;
    }
    case WM_MOUSEMOVE:
    {
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = 1;
        tme.hwndTrack = hWnd;
        BOOL boRet = _TrackMouseEvent(&tme);
    }break;
    case WM_MOUSELEAVE:
    {

        //PAINTSTRUCT ps1;
        HBRUSH hbr = NULL;
        HPEN hpen = NULL;
        hdc = GetDC(hWnd);


        hbr = CreateSolidBrush(UICOLOR_BUTTON);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, UICOLOR_BUTTON_TEXT);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

        DrawFrameBtn(hdc, hpen, rc, 2, UICOLOR_BUTTON);

        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
        DeleteObject(hbr);
        DeleteObject(hpen);
        OutputDebugStringA("Leave\n");
        break;
    }
    case WM_MOUSEHOVER:
    {
        HBRUSH hbr = NULL;
        hdc = GetDC(hWnd);

        HPEN hpen = NULL;

        hbr = CreateSolidBrush(UICOLOR_BUTTON_HOVER);
        SelectObject(hdc, hbr);
        FillRect(hdc, &rc, hbr);
        GetWindowText(hWnd, txt, 40);
        SetTextColor(hdc, UICOLOR_BUTTON_TEXT);
        SetBkMode(hdc, TRANSPARENT);
        if (hFont == 0)
        {
            memset(&lf, 0, sizeof(LOGFONT));
            lf.lfHeight = -16;
            wcscpy(lf.lfFaceName, L"黑体");
            hFont = CreateFontIndirect(&lf);  // create the font
        }
        HFONT old = (HFONT)SelectObject(hdc, hFont);
        DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);


        DrawFrameBtn(hdc, hpen, rc, 2, GOON);


        ReleaseDC(hWnd, hdc);
        DeleteObject(hbr);
        OutputDebugStringA("Over\n");
        break;
    }
    }
    //
    return CallWindowProc(ButtonProc, hWnd, Msg, wParam, lParam);
}
//HWND 主窗口,__x1 x坐标,__x2 y坐标,L"按钮文字",从定义获取控件
//如果需要进行消息处理,case IDC_XX:
int VertexUIButton(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,
    LPCTSTR in,
    UINT style //
)
{
    using namespace::NormalButton; 

    int len = wcslen(in);
    if(len > 3)
    {
        if (wcslen(in)%2 < 1)
        {
            len = len *2* 9 + 18;
        }
        else
        {
            len = len * 8 + 20;
        }
    }
    else
    {
        len = 60;
    }

    static HFONT hFont;
    BTN_PARAM btn;
    btn.hWnd = hWnd;
    btn.style = style;
    g_bt1 = CreateWindow(L"Button", in, WS_OVERLAPPED| WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_TEXT | BS_OWNERDRAW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//默认按钮样式
        x1, x2, len, 30, hWnd, (HMENU)style, b_hInstance, NULL);
    ButtonProc = (WNDPROC)SetWindowLongPtr(g_bt1, GWLP_WNDPROC, (LONG_PTR)BTProc);
    return -1;
}

int VertexUIButtonEx(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,
    BOOL rectx,BOOL recty,
    LPCTSTR in,
    UINT style //
)
{
    using namespace::NormalButton;

    static HFONT hFont;
    BTN_PARAM btn;
    btn.hWnd = hWnd;
    btn.style = style;
    g_bt1 = CreateWindow(L"Button", in, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_TEXT | BS_OWNERDRAW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//默认按钮样式
        x1, x2, rectx, recty, hWnd, (HMENU)style, b_hInstance, NULL);
    ButtonProc = (WNDPROC)SetWindowLongPtr(g_bt1, GWLP_WNDPROC, (LONG_PTR)BTProc);
    return -1;
}

#pragma once
/*
* VertexUI Child Window 
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
#include "VertexUI.ctlAnime.h"
#pragma warning(disable:4996)

#ifdef SimpleCode
#define TipBox VertexUITipBox
#define TipBoxEx VertexUITipBoxEx
#endif

#define PANELSTYLE_AUTOLEN 0xdd0
#define PANEL_TEST 0xdd1

namespace NormalPanel {
    HINSTANCE ti_hInstance;
    HWND c_tip1;
    HWND c_tip2;
    WNDPROC TipBoxProc;
    WNDPROC BTold;

    typedef struct TagTipBox
    {// 
        HWND hWnd;
        BOOL x1;
        BOOL x2;
        LPWSTR in;
        UINT style;
    } TIP_PARAM;
    int NormalTipHeight = 40;
    int nh = NormalTipHeight;
    void DrawFramePanel(HDC hdc, HPEN hpen, RECT rect, BOOL wid, COLORREF cl)
    {
        hpen = CreatePen(PS_SOLID, wid, cl);
        SelectObject(hdc, hpen);
        SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
        //Rectangle(hdc, 0, 0, rect.right - rect.left, rect.bottom - rect.top);
        Rectangle(hdc, 1, 1, rect.right - rect.left , rect.bottom - rect.top );
    }
    HWND tibtnhwnd;
    HINSTANCE tibtnHINST;
    WNDPROC tiBToldProc;
    typedef struct tagCLOSE
    {// 
        HWND hWnd;          // 主窗口 handle of owner window
        BOOL x1; //x坐标 x axis
        BOOL x2; //y坐标 y axis
        LPWSTR in; //NO USE
        UINT style; //从定义里获取依赖,处理消息 Get Messages from define
    } CLOASE_PARAM;
    //
    //
    LRESULT CALLBACK tiBTclose(HWND hWnd, UINT_PTR Msg, WPARAM wParam, LPARAM lParam)
    {// 
        PAINTSTRUCT ps;
        HDC hdc = NULL;
        RECT rc;
        GetClientRect(hWnd, &rc);
        LOGFONT lf;
        HFONT hFont = 0;
        HBRUSH br;
        HPEN hpen;
        //TCHAR txt[40];
        switch (Msg)
        {//
        case WM_PAINT: //绘制图形 Draw the Shape(line)of "close"
        {
            RedrawWindow(hWnd,&rc,NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
            PAINTSTRUCT ps1;
            hdc = BeginPaint(hWnd, &ps1);

            HBRUSH hbr = NULL;
            hdc = GetDC(hWnd);
            hbr = CreateSolidBrush(UICOLOR_PANEL);
            SelectObject(hdc, hbr);
            FillRect(hdc, &rc, hbr);
            //SetWindowText(hWnd, L"关闭");
            hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
            SelectObject(hdc, hpen);
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, 10, 10);
            MoveToEx(hdc, 10, 0, NULL);
            LineTo(hdc, 0, 10);
            ReleaseDC(hWnd, hdc);
            DeleteObject(hbr);
            DeleteObject(hpen);
            EndPaint(hWnd, &ps1);
            break;
        }
        case WM_MOUSEMOVE: //悬停变色 Mosehover and ColorChange
        {
            TRACKMOUSEEVENT tme;
            tme.cbSize = sizeof(tme);
            tme.dwFlags = TME_HOVER | TME_LEAVE;
            tme.dwHoverTime = 1;
            tme.hwndTrack = hWnd;
            BOOL boRet = _TrackMouseEvent(&tme);
        }break;
        case WM_MOUSELEAVE: //鼠标离开,颜色复原 If mouse leave,reset the color
        {

            PAINTSTRUCT ps1;
            HBRUSH hbr = NULL;
            hdc = GetDC(hWnd);
            hbr = CreateSolidBrush(UICOLOR_PANEL);
            SelectObject(hdc, hbr);
            FillRect(hdc, &rc, hbr);
            //SetWindowText(hWnd, L"关闭");
            hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
            SelectObject(hdc, hpen);
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, 10, 10);
            MoveToEx(hdc, 10, 0, NULL);
            LineTo(hdc, 0, 10);
            ReleaseDC(hWnd, hdc);
            DeleteObject(hbr);
            DeleteObject(hpen);
            OutputDebugStringA("Leave\n");
            break;
        }
        case WM_MOUSEHOVER: //鼠标放在按钮上,变色 Mouse on the button,Change the color
        {
            HBRUSH hbr = NULL;
            hdc = GetDC(hWnd);
            hbr = CreateSolidBrush(peachred);
            hpen = CreatePen(PS_SOLID, 2, RGB(244, 244, 244));
            SelectObject(hdc, hbr);
            FillRect(hdc, &rc, hbr);
            SelectObject(hdc, hpen);
            MoveToEx(hdc, 0, 0, NULL);
            LineTo(hdc, 10, 10);
            MoveToEx(hdc, 10, 0, NULL);
            LineTo(hdc, 0, 10);
            ReleaseDC(hWnd, hdc);
            //SetWindowText(hWnd, L"[关闭]");
            DeleteObject(hbr);
            DeleteObject(hpen);
            OutputDebugStringA("Over\n");
            break;
        }

        }
        //
        return CallWindowProc(tiBToldProc, hWnd, Msg, wParam, lParam);
    }
    int PanelFrameClose(
        HWND hWnd,         // handle of owner window
        BOOL x1,
        BOOL x2,

        UINT style //从定义获取按钮控件依赖
    )
    {
        static HFONT hFont;
        CLOASE_PARAM btn;
        btn.hWnd = hWnd;
        btn.style = style;
        tibtnhwnd = CreateWindow(L"Button", NULL, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW,//默认按钮样式
            x1, x2, 11,11, hWnd, (HMENU)style, tibtnHINST, NULL);
        tiBToldProc = (WNDPROC)SetWindowLongPtr(tibtnhwnd, GWLP_WNDPROC, (LONG_PTR)tiBTclose);
        return -1;
    }
}

#define PANEL_BTN_CLOSE 0xc11
#define VERTEXUI_TIPBOX_CREATE 0xc10
//
//
LRESULT CALLBACK CTipProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{// 
    using namespace::NormalPanel;
    PAINTSTRUCT ps;
    HDC hdc = NULL;
    RECT rc;
    GetClientRect(hWnd, &rc);
    LOGFONT lf;
    HFONT hFont = 0;
    HBRUSH br;
    TCHAR txt[40];

    TIP_PARAM* pmmb = (TIP_PARAM*)lParam;
    UNREFERENCED_PARAMETER(lParam);

    switch (Msg)
    {//
    case VERTEXUI_TIPBOX_CREATE:
    {
        SetFocus(hWnd);
        PanelFrameClose(hWnd, rc.right - 20, 10, PANEL_BTN_CLOSE);
        OutputDebugStringA("\nTipBox init!");//
        break;
    }
    case WM_PAINT:
    {
        HBRUSH hbr = NULL;
        HPEN hpen = 0;
        HPEN hpf = 0;
        hdc = BeginPaint(hWnd, &ps);


        hbr = CreateSolidBrush(UICOLOR_PANEL);
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

        DrawFramePanel(hdc, hpen, rc, 2, UICOLOR_PANEL_FRAME);

        ReleaseDC(hWnd, hdc);
        UpdateWindow(hWnd);
        DeleteObject(hbr);
        DeleteObject(hpen);
        EndPaint(hWnd, &ps);
        OutputDebugStringA("TIPBOX_PANEL PAINT");

        break;
    }
    case WM_LBUTTONDOWN:
    {
        // 移动窗口 
        SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);  //向窗口发送WM_NCLBUTTONDOWN消息，HTCAPTION 标题
        break;
    }
    case WM_MOVING:
    {
        break;
    }
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case PANEL_BTN_CLOSE:
        {
            EndDialog(hWnd, 0);
        }
        }
        break;
    }
    }
    //
    return CallWindowProc(TipBoxProc, hWnd, Msg, wParam, lParam); 

}


//HWND 主窗口,__x1 x坐标,__x2 y坐标,L"文字",对应的消息处理
//如果需要进行消息处理,case IDC_XX:
int VertexUITipBox(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,
    LPCTSTR in
)
{
    using namespace::NormalPanel;

    int len = wcslen(in);
    if (len > 3)
    {
        if (wcslen(in) % 2 < 1)
        {
            len = len * 2 * 9 + 18;
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

    TIP_PARAM tip;
    tip.hWnd = hWnd;
    c_tip1 = CreateWindow(L"#32770", in, WS_OVERLAPPED|WS_VISIBLE | WS_CHILD |WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
        x1, x2, len, 90, hWnd, nullptr, ti_hInstance , NULL);
    TipBoxProc = (WNDPROC)SetWindowLongPtr(c_tip1, GWLP_WNDPROC, (LONG_PTR)CTipProc);
    SendMessage(c_tip1, VERTEXUI_TIPBOX_CREATE, 0, 0);

    return -1;
}

int VertexUITipBoxEx(
    HWND hWnd,         // handle of owner window
    BOOL x1,
    BOOL x2,
    BOOL rectx, BOOL recty,
    LPCTSTR in,
    UINT style //
)
{
    using namespace::NormalPanel;

    static HFONT hFont;
    TIP_PARAM btn;
    btn.hWnd = hWnd;
    btn.style = style;

    if (style == PANELSTYLE_AUTOLEN)
    {
        int len = wcslen(in);
        if (len > 3)
        {
            if (wcslen(in) % 2 == 0)
            {
                len = len * 2 * 9 + 18;
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
        rectx = len;
    }


    TIP_PARAM tip;
    tip.hWnd = hWnd;
    tip.style = style;
    c_tip1 = CreateWindow(L"#32770", in, WS_OVERLAPPED | WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//TipBox
        x1, x2, rectx, recty, hWnd, nullptr, ti_hInstance, NULL);
    TipBoxProc = (WNDPROC)SetWindowLongPtr(c_tip1, GWLP_WNDPROC, (LONG_PTR)CTipProc);
    SendMessage(c_tip1, VERTEXUI_TIPBOX_CREATE, 0, 0);
    return -1;
}
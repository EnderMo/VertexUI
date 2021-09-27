#pragma once
/*
* 
* VertexUI PanelDrawingInterface
* 
* VertexStudio 2021
* 
*/
#include "framework.h"

#include "VertexUI.Colors.h"

//#define VERTEXUI_DEVMODE

namespace VertexUI
{
    typedef void (DRAWPANEL)(HWND, HDC);
    int PanelID = 0;
    int PrevPanelID = 0;
    namespace Panel
    {
        //CreatePanel only passed in parameters below:(HWND,HDC).

        //It convert (x,y,sizex,sizey) into RECT {x,y,x+sizex,y+sizey}.
        void RectTypeConvert(RECT &rc, int x, int y, int sizex, int sizey)
        {
            rc = { x,y,x + sizex,y + sizey };
        }
        
        //DrawRect
        void CreateRect(HWND h, HDC hdc, int x,int y,int sizex,int sizey,COLORREF cl)
        {
            RECT mRc;
            RectTypeConvert(mRc, x, y, sizex, sizey);
            HBRUSH hb = CreateSolidBrush(cl);
            HBRUSH bhb = (HBRUSH)SelectObject(hdc,hb);
            SelectObject(hdc, hb);
            FillRect(hdc, &mRc, hb);
            SelectObject(hdc, bhb);
            DeleteObject(hb);
        }

        //Fill the whole window
        void CreateFillArea(HWND h, HDC hdc, COLORREF cl)
        {
            RECT Rc;
            GetClientRect(h,&Rc);
            RectTypeConvert(Rc, Rc.left,Rc.top, Rc.right, Rc.bottom);
            HBRUSH hb = CreateSolidBrush(cl);
            HBRUSH bhb = (HBRUSH)SelectObject(hdc, hb);
            SelectObject(hdc, hb);
            FillRect(hdc, &Rc, hb);
            SelectObject(hdc, bhb);
            DeleteObject(hb);
        }

        //Text
        void TextPreDraw(HDC hdc, int x,int y,int sizex,int sizey, LPTSTR txt, COLORREF cl)
        {
            RECT rc;
            RectTypeConvert(rc,x, y, sizex, sizey);
            LOGFONT lf;
            HFONT hFont = 0;
            SetTextColor(hdc, cl);
            SetBkMode(hdc, TRANSPARENT);
            if (hFont == 0)
            {
                memset(&lf, 0, sizeof(LOGFONT));
                lf.lfHeight = -18;
                wcscpy_s(lf.lfFaceName, L"Segoe UI");
                hFont = CreateFontIndirect(&lf);  // create the font
            }
            HFONT old = (HFONT)SelectObject(hdc, hFont);
            DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            DeleteObject(hFont);
            SelectObject(hdc, old);
        }
        
        //Button
        void CreateSimpleButton(HWND h,HDC hdc,int x, int y, int sizex, int sizey,LPTSTR s)
        {
            CreateRect(h, hdc, x, y, sizex, sizey, VERTEXUI_GREENSEA);
            TextPreDraw(hdc, x, y, sizex, sizey, s, VERTEXUI_WHITE);
        }

        //Create a Drawing Panel.
        void CreatePanel(HWND h, HDC hdc, DRAWPANEL DrawFun)
        {
            HDC         hMemDC;
            HBITMAP     hBmpMem;
            HBITMAP     hPreBmp;
            RECT rc;
            GetClientRect(h, &rc);
            hMemDC = CreateCompatibleDC(hdc);

            hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

            hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
            //On hMemDC.
            DrawFun(h, hMemDC);

            BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);


            SelectObject(hMemDC, hPreBmp);


            DeleteObject(hBmpMem);

            DeleteDC(hMemDC);
        }

        //
        void CreatePanelByID(HWND h, HDC hdc, DRAWPANEL DrawFun,int ID)
        {
            HDC         hMemDC;
            HBITMAP     hBmpMem;
            HBITMAP     hPreBmp;
            RECT rc;
            GetClientRect(h, &rc);
            //InvalidateRect(h, &rc, 1);
            hMemDC = CreateCompatibleDC(hdc);

            hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

            hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
            //On hMemDC.
            if (PanelID == ID)
            {
                DrawFun(h, hMemDC);
            }

            BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);


            SelectObject(hMemDC, hPreBmp);


            DeleteObject(hBmpMem);

            DeleteDC(hMemDC);
        }

        //
        void SwitchPanel(DRAWPANEL p,int ID)
        {
            PanelID = ID;
        }

        void SetPanelID(int id)
        {
            PrevPanelID = PanelID;
            PanelID = id;
        }
    }
}

#ifdef VERTEXUI_DEVMODE
using namespace::VertexUI;
using namespace::VertexUI::Panel;
void XSleep(UINT Delay_ms)
{
    DWORD dwTick = GetTickCount64() + Delay_ms;
    while (GetTickCount64() < dwTick)
    {
        MSG msg;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Sleep(0);
    }
}
int anistat = 0;
int CreatePanelAnimation(HWND h, HDC hdc, DRAWPANEL DrawFun)
{
    HDC         hMemDC;
    HBITMAP     hBmpMem;
    HBITMAP     hPreBmp;
    RECT rc;
    GetClientRect(h, &rc);
    //InvalidateRect(h, &rc, 1);
    hMemDC = CreateCompatibleDC(hdc);

    hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

    hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
    //On hMemDC.
    DrawFun(h, hMemDC);
    if (anistat == 1)
    {
        BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        anistat = 0;
        return -1;
    }
    if (anistat == 0)
    {
        BitBlt(hdc, 300, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 295, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 282, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 262, 0,rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 243, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 214, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 171, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 116, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 71, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 41, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 29, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 17, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 11, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 8, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 5, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 3, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 2, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 1, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        XSleep(10);
        BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
        SelectObject(hMemDC, hPreBmp);


        DeleteObject(hBmpMem);

        DeleteDC(hMemDC);
        anistat = 1;
        return -1;
    }

    SelectObject(hMemDC, hPreBmp);


    DeleteObject(hBmpMem);

    DeleteDC(hMemDC);

    return 0;
}
int _VertexUI_PanelFlag = 0;
void CreatePanelByFlag(HWND h, HDC hdc, DRAWPANEL DrawFun)
{

    //On hMemDC.
    if (PanelID == PrevPanelID)
    {
        CreatePanel(h, hdc, DrawFun);
        anistat = 0;
    }
    if (PanelID != PrevPanelID)
    {
        CreatePanelAnimation(h, hdc, DrawFun);
        PrevPanelID = PanelID;
        anistat = 0;
    }
}
#endif
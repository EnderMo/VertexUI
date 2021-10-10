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
#include <assert.h>

#define VERTEXUI_DEVMODE

namespace VertexUI
{
    typedef void (DRAWPANEL)(HWND, HDC);
    typedef void (SDRAWPANEL)(HDC);
    typedef struct VERTEXUICTL {
        int x;
        int y;
        int sizex;
        int sizey;
        const wchar_t* Text;
    }TagVUICTL;
    const wchar_t* PanelID = L"Init";
    const wchar_t* PrevPanelID = L"Init";
    const wchar_t* ButtonText = L"Button";
    int g_hoverstate = 0;
    namespace Panel
    {
        //CreatePanel only passed in parameters below:(HWND,HDC).

        //It convert (x,y,sizex,sizey) into RECT {x,y,x+sizex,y+sizey}.
        void RectTypeConvert(RECT& rc, int x, int y, int sizex, int sizey)
        {
            rc = { x,y,x + sizex,y + sizey };
        }

        //DrawRect
        void CreateRect(HWND h, HDC hdc, int x, int y, int sizex, int sizey, COLORREF cl)
        {
            RECT mRc;
            RectTypeConvert(mRc, x, y, sizex, sizey);
            HBRUSH hb = CreateSolidBrush(cl);
            HBRUSH bhb = (HBRUSH)SelectObject(hdc, hb);
            SelectObject(hdc, hb);
            FillRect(hdc, &mRc, hb);
            SelectObject(hdc, bhb);
            DeleteObject(hb);
        }

        //Fill the whole window
        void CreateFillArea(HWND h, HDC hdc, COLORREF cl)
        {
            RECT Rc;
            GetClientRect(h, &Rc);
            RectTypeConvert(Rc, Rc.left, Rc.top, Rc.right, Rc.bottom);
            HBRUSH hb = CreateSolidBrush(cl);
            HBRUSH bhb = (HBRUSH)SelectObject(hdc, hb);
            SelectObject(hdc, hb);
            FillRect(hdc, &Rc, hb);
            SelectObject(hdc, bhb);
            DeleteObject(hb);
        }

        //Text
        void TextPreDraw(HDC hdc, int x, int y, int sizex, int sizey, const wchar_t* txt, COLORREF cl)
        {
            RECT rc;
            RectTypeConvert(rc, x, y, sizex, sizey);
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

        //Flags: 0.ToLeft 1.Center 
        void TextPreDrawEx(HDC hdc, int x, int y, int sizex, int sizey, const wchar_t* txt, int sz, int flag, COLORREF cl)
        {
            RECT rc;
            RectTypeConvert(rc, x, y, sizex, sizey);
            LOGFONT lf;
            HFONT hFont = 0;
            SetTextColor(hdc, cl);
            SetBkMode(hdc, TRANSPARENT);
            if (hFont == 0)
            {
                memset(&lf, 0, sizeof(LOGFONT));
                lf.lfHeight = -sz;
                wcscpy_s(lf.lfFaceName, L"Segoe UI");
                hFont = CreateFontIndirect(&lf);  // create the font
            }
            HFONT old = (HFONT)SelectObject(hdc, hFont);
            if (flag == 0)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_VCENTER);
            }
            if (flag == 1)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }
            if (flag == 2)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE);
            }
            DeleteObject(hFont);
            SelectObject(hdc, old);
        }
        void _TextPreDrawEx(HDC hdc, int x, int y, int sizex, int sizey, const wchar_t* txt, int sz, const wchar_t* Font, int flag, COLORREF cl)
        {
            RECT rc;
            RectTypeConvert(rc, x, y, sizex, sizey);
            LOGFONT lf;
            HFONT hFont = 0;
            SetTextColor(hdc, cl);
            SetBkMode(hdc, TRANSPARENT);
            if (hFont == 0)
            {
                memset(&lf, 0, sizeof(LOGFONT));
                lf.lfHeight = -sz;
                lf.lfQuality = ANTIALIASED_QUALITY;
                wcscpy_s(lf.lfFaceName, Font);
                hFont = CreateFontIndirect(&lf);  // create the font
            }
            HFONT old = (HFONT)SelectObject(hdc, hFont);
            if (flag == 0)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_VCENTER);
            }
            if (flag == 1)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            }
            if (flag == 2)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_SINGLELINE);
            }
            if (flag == 3)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_CENTER | DT_VCENTER);
            }
            if (flag == 4)
            {
                DrawText(hdc, txt, wcslen(txt), &rc, DT_VCENTER);
            }
            DeleteObject(hFont);
            SelectObject(hdc, old);
        }
        //Only straight Line
        void PanelDrawSTLine(HDC pDC, int X0, int Y0, int X1, int Y1, COLORREF clrLine)
        {
            if (Y0 > Y1) { int Temp = Y0; Y0 = Y1; Y1 = Temp; Temp = X0; X0 = X1; X1 = Temp; }SetPixel(pDC, X0, Y0, clrLine);
            int XDir, DeltaX = X1 - X0; if (DeltaX >= 0) { XDir = 1; }
            else { XDir = -1; DeltaX = 0 - DeltaX; }int DeltaY = Y1 - Y0;
            if (DeltaY == 0) { while (DeltaX-- != 0) { X0 += XDir; SetPixel(pDC, X0, Y0, clrLine); }return; }
            if (DeltaX == 0) { do { Y0++; SetPixel(pDC, X0, Y0, clrLine); } while (--DeltaY != 0); return; }
            if (DeltaX == DeltaY) { do { X0 += XDir; Y0++; SetPixel(pDC, X0, Y0, clrLine); } while (--DeltaY != 0); return; }SetPixel(pDC, X1, Y1, clrLine);
        }

        //Frame

        void PanelDrawOutFrame(HWND h, HDC hdc, COLORREF cl)
        {
            RECT rc;
            GetClientRect(h, &rc);
            PanelDrawSTLine(hdc, 0, 0, rc.right, 0, cl);
            PanelDrawSTLine(hdc, 0, 0, 0, rc.bottom, cl);
            PanelDrawSTLine(hdc, 0, rc.bottom - 1, rc.right - rc.left, rc.bottom - 1, cl);
            PanelDrawSTLine(hdc, rc.right - 1, 0, rc.right - 1, rc.bottom - 1, cl);
        }
        void PanelDrawCloseBtn(HWND h, HDC hdc, int x, int y, int x1, int y1, int inframepos, COLORREF cl)
        {
            RECT rc;
            RectTypeConvert(rc, x, y, x1, y1);
            HPEN hpen;
            hpen = CreatePen(PS_SOLID, 1, cl);
            HPEN prhp = (HPEN)SelectObject(hdc, hpen);
            SelectObject(hdc, hpen);
            MoveToEx(hdc, rc.left + inframepos + 1, rc.top + inframepos + 1, NULL);
            LineTo(hdc, rc.right - inframepos, rc.bottom - inframepos);

            MoveToEx(hdc, rc.left + inframepos + 1, rc.bottom - inframepos - 1, NULL);
            LineTo(hdc, rc.right - inframepos, rc.top + inframepos);
            DeleteObject(hpen);
            SelectObject(hdc, prhp);
        }

        //Button
        void CreateSimpleButton(HWND h, HDC hdc, int x, int y, int sizex, int sizey, const wchar_t* s)
        {
            CreateRect(h, hdc, x, y, sizex, sizey, VERTEXUI_GREENSEA);
            TextPreDraw(hdc, x, y, sizex, sizey, s, VERTEXUI_WHITE);
        }

        //Custom Color Button
        void CreateSimpleButtonEx(HWND h, HDC hdc, int x, int y, int sizex, int sizey, COLORREF cl, const wchar_t* s)
        {
            int tsz = 0;
            CreateRect(h, hdc, x, y, sizex, sizey, cl);
            if (sizey > 23)
            {
                tsz = 18;
            }
            else
            {
                tsz = 16;
            }
            TextPreDrawEx(hdc, x, y, sizex, sizey, s, tsz, 1, VERTEXUI_WHITE);
        }

        //Create a Drawing Panel.
        void _CreatePanel(HWND h, HDC hdc, DRAWPANEL DrawFun)
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
        void CreatePanel(HWND h, HDC hdc, DRAWPANEL DrawFun, const wchar_t* ID)
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

            BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);


            SelectObject(hMemDC, hPreBmp);


            DeleteObject(hBmpMem);

            DeleteDC(hMemDC);
        }

        //
        void SwitchPanel(DRAWPANEL p, const wchar_t* ID)
        {
            PanelID = ID;
        }

        void SetPanelID(const wchar_t* id)
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
struct PanelHandleFun
{
    HDC hdc;
    HDC hmdc;
    RECT rc;
    HBITMAP hpbp;
    HBITMAP hmbp;
};
int anistat = 0;
DWORD WINAPI VUIPAnimationThread(LPVOID pf)
{
    PanelHandleFun* p = (PanelHandleFun*)pf;
    HDC hdc = p->hdc;
    HDC hMemDC = p->hmdc;
    RECT rc = p->rc;
    HBITMAP hPreBmp = p->hpbp;
    HBITMAP hBmpMem = p->hmbp;
    BitBlt(hdc, 300, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
    XSleep(10);
    BitBlt(hdc, 295, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
    XSleep(10);
    BitBlt(hdc, 282, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
    XSleep(10);
    BitBlt(hdc, 262, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
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
    return 0;
}
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
        PanelHandleFun p{};
        p.hdc = hdc;
        p.hmdc = hMemDC;
        p.rc = rc;
        p.hpbp = hPreBmp;
        p.hmbp = hBmpMem;
        HANDLE thread = CreateThread(NULL, NULL, VUIPAnimationThread, &p, 0, 0);
        if (thread)
        {
            WaitForSingleObject(thread, INFINITE); //Òª²¥ÍêÔÙ¹ØÄØ
            CloseHandle(thread);
        }

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
        _CreatePanel(h, hdc, DrawFun);
        anistat = 0;
    }
    if (PanelID != PrevPanelID)
    {
        CreatePanelAnimation(h, hdc, DrawFun);
        PrevPanelID = PanelID;
        anistat = 0;
    }
}
void TESTDrawLine(HDC pDC, int X0, int Y0, int X1, int Y1, COLORREF clrLine)
{
    HDC mDC = pDC;
    if (Y0 > Y1)
    {
        int Temp = Y0; Y0 = Y1; Y1 = Temp;
        Temp = X0; X0 = X1; X1 = Temp;
    }

    SetPixel(pDC, X0, Y0, clrLine);

    int XDir, DeltaX = X1 - X0;
    if (DeltaX >= 0)
    {
        XDir = 1;
    }
    else
    {
        XDir = -1;
        DeltaX = 0 - DeltaX;
    }

    int DeltaY = Y1 - Y0;
    if (DeltaY == 0)
    {
        /* Horizontal line */
        while (DeltaX-- != 0)
        {
            X0 += XDir;
            SetPixel(pDC, X0, Y0, clrLine);
        }
        return;
    }
    if (DeltaX == 0)
    {
        /* Vertical line */
        do
        {
            Y0++;
            SetPixel(pDC, X0, Y0, clrLine);
        } while (--DeltaY != 0);
        return;
    }

    if (DeltaX == DeltaY)
    {
        /* Diagonal line */
        do
        {
            X0 += XDir;
            Y0++;
            SetPixel(pDC, X0, Y0, clrLine);
        } while (--DeltaY != 0);
        return;
    }

    unsigned short ErrorAdj;
    unsigned short ErrorAccTemp, Weighting;


    unsigned short ErrorAcc = 0;

    BYTE rl = GetRValue(clrLine);
    BYTE gl = GetGValue(clrLine);
    BYTE bl = GetBValue(clrLine);
    double grayl = rl * 0.299 + gl * 0.587 + bl * 0.114;

    if (DeltaY > DeltaX)
    {

        ErrorAdj = ((unsigned long)DeltaX << 16) / (unsigned long)DeltaY;
        while (--DeltaY) {
            ErrorAccTemp = ErrorAcc;
            ErrorAcc += ErrorAdj;
            if (ErrorAcc <= ErrorAccTemp) {

                X0 += XDir;
            }
            Y0++;

            Weighting = ErrorAcc >> 8;
            assert(Weighting < 256);
            assert((Weighting ^ 255) < 256);

            COLORREF clrBackGround = ::GetPixel(mDC, X0, Y0);
            BYTE rb = GetRValue(clrBackGround);
            BYTE gb = GetGValue(clrBackGround);
            BYTE bb = GetBValue(clrBackGround);
            double grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

            BYTE rr = (rb > rl ? ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (rb - rl) + rl)) : ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (rl - rb) + rb)));
            BYTE gr = (gb > gl ? ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (gb - gl) + gl)) : ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (gl - gb) + gb)));
            BYTE br = (bb > bl ? ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (bb - bl) + bl)) : ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (bl - bb) + bb)));
            SetPixel(pDC, X0, Y0, RGB(rr, gr, br));

            clrBackGround = ::GetPixel(mDC, X0 + XDir, Y0);
            rb = GetRValue(clrBackGround);
            gb = GetGValue(clrBackGround);
            bb = GetBValue(clrBackGround);
            grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

            rr = (rb > rl ? ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (rb - rl) + rl)) : ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (rl - rb) + rb)));
            gr = (gb > gl ? ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (gb - gl) + gl)) : ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (gl - gb) + gb)));
            br = (bb > bl ? ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (bb - bl) + bl)) : ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (bl - bb) + bb)));
            SetPixel(pDC, X0 + XDir, Y0, RGB(rr, gr, br));
        }

        SetPixel(pDC, X1, Y1, clrLine);
        return;
    }

    ErrorAdj = ((unsigned long)DeltaY << 16) / (unsigned long)DeltaX;

    while (--DeltaX) {
        ErrorAccTemp = ErrorAcc;
        ErrorAcc += ErrorAdj;
        if (ErrorAcc <= ErrorAccTemp) {

            Y0++;
        }
        X0 += XDir;

        Weighting = ErrorAcc >> 8;
        assert(Weighting < 256);
        assert((Weighting ^ 255) < 256);

        COLORREF clrBackGround = ::GetPixel(mDC, X0, Y0);
        BYTE rb = GetRValue(clrBackGround);
        BYTE gb = GetGValue(clrBackGround);
        BYTE bb = GetBValue(clrBackGround);
        double grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

        BYTE rr = (rb > rl ? ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (rb - rl) + rl)) : ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (rl - rb) + rb)));
        BYTE gr = (gb > gl ? ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (gb - gl) + gl)) : ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (gl - gb) + gb)));
        BYTE br = (bb > bl ? ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (bb - bl) + bl)) : ((BYTE)(((double)(grayl < grayb ? Weighting : (Weighting ^ 255))) / 255.0 * (bl - bb) + bb)));

        SetPixel(pDC, X0, Y0, RGB(rr, gr, br));

        clrBackGround = ::GetPixel(mDC, X0, Y0 + 1);
        rb = GetRValue(clrBackGround);
        gb = GetGValue(clrBackGround);
        bb = GetBValue(clrBackGround);
        grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

        rr = (rb > rl ? ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (rb - rl) + rl)) : ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (rl - rb) + rb)));
        gr = (gb > gl ? ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (gb - gl) + gl)) : ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (gl - gb) + gb)));
        br = (bb > bl ? ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (bb - bl) + bl)) : ((BYTE)(((double)(grayl < grayb ? (Weighting ^ 255) : Weighting)) / 255.0 * (bl - bb) + bb)));

        SetPixel(pDC, X0, Y0 + 1, RGB(rr, gr, br));
    }

    SetPixel(pDC, X1, Y1, clrLine);
}
void CreateButton(HWND hWnd, HDC hdc, int x, int y, int sizex, int sizey, int cid, const wchar_t* CTLTXT)
{
    //VERTEXUICTL btn;
    //btn.Text = L"114514";
    CreateSimpleButton(hWnd, hdc, x, y, sizex, sizey, CTLTXT);
}


void DrawGradient(HDC pDC, RECT rRect, COLORREF crFrom, COLORREF crTo)
{

    int iHeight = rRect.bottom - rRect.top;

    int iWidth = (rRect.right - rRect.left);

    //

    int iR = GetRValue(crFrom);

    int iG = GetGValue(crFrom);

    int iB = GetBValue(crFrom);

    //

    int idR = (256 * (GetRValue(crTo) - iR)) / iWidth;

    int idG = (256 * (GetGValue(crTo) - iG)) / iWidth;

    int idB = (256 * (GetBValue(crTo) - iB)) / iWidth;



    iR *= 256;

    iG *= 256;

    iB *= 256;

    // ->

    for (int i = rRect.left; i <= iWidth; i++, iR += idR, iG += idG, iB += idB)
    {
        RECT rcx;
        RectTypeConvert(rcx, i, rRect.top, 1, iHeight);
        HBRUSH hbr = CreateSolidBrush(RGB(iR / 256, iG / 256, iB / 256));
        HBRUSH hOld = (HBRUSH)SelectObject(pDC, hbr);
        FillRect(pDC, &rcx, hbr);
        DeleteObject(hbr);
        SelectObject(pDC, hOld);
    }

}

//Other


#endif
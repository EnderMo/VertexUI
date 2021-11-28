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
#define VERTEXUI_FLAGS_ANIMATION 0

#define VERTEXUI_FLAGS_NOANIMATION 1

#define VERTEXUI_FLAGS_MEMDRAW 2

#define VERTEXUI_FLAGS_CACHE 1

#define VERTEXUI_DEVMODE

#define RCWID (rc.right -rc.left)

#define InitCtl(ctlname,x,y,cx,cy,fun,txt) {ctlname,x,y,cx,cy,fun,txt}
namespace VertexUI
{
	typedef void (DRAWPANEL)(HWND, HDC);

	typedef void (SDRAWPANEL)(HDC);
	typedef struct VERTEXUICTL {
		const wchar_t* CtlName;
		int x;
		int y;
		int sizex;
		int sizey;
		int (*runfun)() = 0;
		const wchar_t* Text;
	}VUICTL;
	typedef struct PanelHandleFun
	{
		HDC hdc;
		HDC hmdc;
		RECT rc;
		HBITMAP hpbp;
		HBITMAP hmbp;
		int x;
		int y;
		int cx;
		int cy;
		DRAWPANEL* exDraw;
		COLORREF c1;
		COLORREF c2;
		HWND h;
	};
	typedef struct PanelDCCache
	{
		HDC inhdc;//兼容VertexUI内建
		HDC hdc;
		HDC hMemDC;
	};
	int dystate = 1;
	const wchar_t* ListPanel = L"ListPanel";
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
			if (flag == 3)
			{
				DrawText(hdc, txt, wcslen(txt), &rc, DT_CENTER | DT_VCENTER);
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
		void PanelDrawDisplayBtn(HWND h, HDC hdc, int x, int y, int x1, int y1, int inframepos, int mdpos, COLORREF cl)
		{
			RECT rc;
			RectTypeConvert(rc, x, y, x1, y1);
			HPEN hpen;
			hpen = CreatePen(PS_SOLID, 1, cl);
			HPEN prhp = (HPEN)SelectObject(hdc, hpen);
			SelectObject(hdc, hpen);
			MoveToEx(hdc, rc.left + inframepos + 1, rc.top + inframepos + 1 + mdpos, NULL);
			LineTo(hdc, rc.left + (x1 / 2) - inframepos, rc.top + (y1 / 2) - inframepos + mdpos);
			MoveToEx(hdc, rc.left + (x1 / 2) + (x1 / 4) - 1 - inframepos - 1, rc.top + inframepos + 1 + mdpos, NULL);
			LineTo(hdc, rc.right - (x1 / 2) - inframepos - 1, rc.bottom - (y1 / 2) - inframepos + mdpos);
			//MoveToEx(hdc, rc.left + inframepos + 1, rc.bottom - inframepos - 1, NULL);
			//LineTo(hdc, rc.right - inframepos, rc.top + inframepos);
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
		void CreateSimpleButtonEx(HWND h, HDC hdc, int x, int y, int sizex, int sizey, COLORREF cl, const wchar_t* s,int ctsz = 0)
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
			if (ctsz != 0)tsz = ctsz;
			TextPreDrawEx(hdc, x, y, sizex, sizey, s, tsz, 1, VERTEXUI_WHITE);
		}

		void DrawRoundRect(HDC hDrawingDC, int x, int y, int cx, int cy, int cornersize, COLORREF cl)
		{
			HPEN hGreenPen = ::CreatePen(PS_SOLID, 2, cl);

			HPEN hOldPen = (HPEN)::GetCurrentObject(hDrawingDC, OBJ_PEN);
			HBRUSH hOldBrush = (HBRUSH)::GetCurrentObject(hDrawingDC, OBJ_BRUSH);

			::SelectObject(hDrawingDC, hGreenPen);
			::SelectObject(hDrawingDC, (HBRUSH)CreateSolidBrush(cl));
			::RoundRect(hDrawingDC, x, y, x + cx, y + cy, cornersize, cornersize);


			::SelectObject(hDrawingDC, hOldBrush);
			::SelectObject(hDrawingDC, hOldPen);
			::DeleteObject(hGreenPen);
		}

		void CreateRoundButton(HDC hdc, int x, int y, int cx, int cy, int cornersize, const wchar_t* txt, COLORREF cl)
		{
			DrawRoundRect(hdc, x, y, cx, cy, cornersize, cl);
			TextPreDraw(hdc, x, y, cx, cy, txt, VERTEXUICOLOR_WHITE);
		}
		void CreateRoundButtonEx(HDC hdc, int x, int y, int cx, int cy, int cornersize, const wchar_t* txt, int txtsz, COLORREF cl)
		{
			DrawRoundRect(hdc, x, y, cx, cy, cornersize, cl);
			TextPreDrawEx(hdc, x, y, cx, cy, txt, txtsz, 1, VERTEXUICOLOR_WHITE);
		}
		void DrawPloygon(HDC hDrawingDC, const POINT* pt, int ang, COLORREF cl)
		{
			HPEN hGreenPen = ::CreatePen(PS_SOLID, 2, cl);

			HPEN hOldPen = (HPEN)::GetCurrentObject(hDrawingDC, OBJ_PEN);
			HBRUSH hOldBrush = (HBRUSH)::GetCurrentObject(hDrawingDC, OBJ_BRUSH);

			::SelectObject(hDrawingDC, hGreenPen);
			::SelectObject(hDrawingDC, (HBRUSH)CreateSolidBrush(cl));
			Polygon(hDrawingDC, pt, ang);


			::SelectObject(hDrawingDC, hOldBrush);
			::SelectObject(hDrawingDC, hOldPen);
			::DeleteObject(hGreenPen);
		}
		void CreateSTab(HDC hdc, int x, int y, bool isopen, int scale = 1)
		{
			if (isopen == false)
			{
				DrawRoundRect(hdc, x * scale, y * scale, 50 * scale, 20 * scale, 15 * scale, VERTEXUICOLOR_MIDNIGHTPLUS);
				DrawRoundRect(hdc, x * scale, y * scale, 20 * scale, 20 * scale, 15 * scale, VERTEXUICOLOR_GREENSEA);
			}
			if (isopen == true)
			{
				DrawRoundRect(hdc, x * scale, y * scale, 50 * scale, 20 * scale, 15 * scale, VERTEXUICOLOR_MIDNIGHTPLUS);
				DrawRoundRect(hdc, (x + 30) * scale, y * scale, 20 * scale, 20 * scale, 15 * scale, VERTEXUICOLOR_GREENSEA);
			}
		}
		void CreateCtl(HWND hWnd,HDC hdc,VUICTL vctl)
		{
			if (vctl.CtlName == L"Button")
			{
				CreateSimpleButton(hWnd, hdc, vctl.x, vctl.y, vctl.sizex, vctl.sizey, vctl.Text);
			}
		}
		HBITMAP hwndToHbitmap(HWND hwnd,HDC hDC)
		{

			//HDC hDC = GetDC(hwnd);


			RECT rect;

			GetClientRect(hwnd, &rect);


			HDC hDCMem = CreateCompatibleDC(hDC);


			HBITMAP hBitMap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);


			HBITMAP hOldMap = (HBITMAP)SelectObject(hDCMem, hBitMap);


			BitBlt(hDCMem, 0, 0, rect.right, rect.bottom, hDC, 0, 0, SRCCOPY);
			hBitMap = (HBITMAP)SelectObject(hDCMem, hOldMap);
			return hBitMap;
		}
		HDC in_ghdc = 0;
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


		void SetPanelID(const wchar_t* id)
		{
			PrevPanelID = PanelID;
			PanelID = id;
		}
		void SwitchPanel(const wchar_t* ID)
		{
			SetPanelID(ID);
			RECT rc;
			GetClientRect(GhWnd, &rc);
			InvalidateRect(GhWnd, &rc, 1);
		}
		void RefreshWindow(HWND h)
		{
			RECT rc;
			GetClientRect(h, &rc);
			dystate = 1;
			InvalidateRect(h, &rc, 0);
		}
	}
	//--


}

namespace VertexUI::Panel
{
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
	DWORD WINAPI VUIPAnimationThread(LPVOID pf)
	{
		PanelHandleFun* p = (PanelHandleFun*)pf;
		HDC hdc = p->hdc;
		HDC hMemDC = p->hmdc;
		RECT rc = p->rc;
		HBITMAP hPreBmp = p->hpbp;
		HBITMAP hBmpMem = p->hmbp;
#ifndef _MINANIMATION
		BitBlt(hdc, rc.right - 2, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 5, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 18, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 36, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 59, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 100, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 158, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 213, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 300, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 350, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 400, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 450, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, rc.right - 530, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
#endif
		BitBlt(hdc, 300, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
#ifdef _MINANIMATION
		XSleep(10);
		BitBlt(hdc, 295, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(10);
		BitBlt(hdc, 282, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
#endif
		XSleep(8);
		BitBlt(hdc, 262, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 243, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 214, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 171, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 116, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 71, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 41, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 29, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 17, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 11, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 8, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 5, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 3, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 2, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
		BitBlt(hdc, 1, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
		XSleep(8);
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
				WaitForSingleObject(thread, INFINITE);
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
	void CreatePanelByFlag(HWND h, HDC hdc, DRAWPANEL DrawFun, int Flag = 0)
	{

		//On hMemDC.
		if (PanelID == PrevPanelID)
		{
			_CreatePanel(h, hdc, DrawFun);
			anistat = 0;
		}
		if (PanelID != PrevPanelID)
		{
			if (Flag == 0)
			{
				CreatePanelAnimation(h, hdc, DrawFun);
			}
			if (Flag == 1)
			{
				_CreatePanel(h, hdc, DrawFun);
			}
			PrevPanelID = PanelID;
			anistat = 0;
		}
	}
	HDC inhdc;

	HBITMAP inbmp;
	HBITMAP CopyBitmap(HBITMAP hbm) {
		HDC hdcSrc = CreateCompatibleDC(NULL);
		HDC hdcDst = CreateCompatibleDC(NULL);
		HBITMAP hbmOld, hbmOld2, hbmNew;
		BITMAP bm;
		GetObject(hbm, sizeof(bm), &bm);
		hbmOld = (HBITMAP)SelectObject(hdcSrc, hbm);
		hbmNew = CreateBitmap(bm.bmWidth, bm.bmHeight, bm.bmPlanes,
			bm.bmBitsPixel,
			NULL);
		hbmOld2 = (HBITMAP)SelectObject(hdcDst, hbmNew);
		BitBlt(hdcDst, 0, 0, bm.bmWidth, bm.bmHeight, hdcSrc, 0, 0, SRCCOPY);
		SelectObject(hdcSrc, hbmOld);
		SelectObject(hdcDst, hbmOld2);
		DeleteDC(hdcSrc);
		DeleteDC(hdcDst);
		return hbmNew;
	}
	int gindc;
	void CreatePanelDynamic(HWND h, HDC hdc, DRAWPANEL DrawFun, int Flag = 0, int updateFlag = 0)
	{

		//On hMemDC.
		if (PanelID == PrevPanelID)
		{
			if (dystate == 0)
			{
				//BitBlt
				RECT rc;
				GetClientRect(h, &rc);
				HDC         hMemDC;
				HBITMAP     hBmpMem;
				HBITMAP     hPreBmp;

				hMemDC = CreateCompatibleDC(hdc);

				hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

				hPreBmp = (HBITMAP)SelectObject(hMemDC, hBmpMem);
				//On hMemDC.

				BitBlt(hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, inhdc, 0, 0, SRCCOPY);
				BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);


				SelectObject(hMemDC, hPreBmp);


				DeleteObject(hBmpMem);

				DeleteDC(hMemDC);
			}
			if (dystate == 1) //First time
			{

				HBITMAP     hBmpMem;
				HBITMAP     hPreBmp;
				RECT rc;
				GetClientRect(h, &rc);
				inhdc = CreateCompatibleDC(hdc);

				hBmpMem = CreateCompatibleBitmap(hdc, rc.right - rc.left, rc.bottom - rc.top);

				hPreBmp = (HBITMAP)SelectObject(inhdc, hBmpMem);
				//On hMemDC.
				DrawFun(h, inhdc);

				BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, inhdc, 0, 0, SRCCOPY);


				//SelectObject(inhdc, hPreBmp);


				DeleteObject(hBmpMem);
				dystate = 0;
			}
			anistat = 0;
		}
		if (PanelID != PrevPanelID)
		{
			if (Flag == 0)
			{
				CreatePanelAnimation(h, hdc, DrawFun);
			}
			if (Flag == 1)
			{
				_CreatePanel(h, hdc, DrawFun);
			}
			if (updateFlag == 0)
			{
				dystate = 1;
			}
			PrevPanelID = PanelID;
			anistat = 0;
		}
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

		int iWidth = rRect.right - 1;

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
	void DrawGradientEx(HDC pDC, int x, int y, int cx, int cy, COLORREF crFrom, COLORREF crTo)
	{

		int iHeight = cy;

		int iWidth = cx;

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

		for (int i = x; i <= iWidth; i++, iR += idR, iG += idG, iB += idB)
		{
			RECT rcx;
			RectTypeConvert(rcx, i, y, 1, iHeight);
			HBRUSH hbr = CreateSolidBrush(RGB(iR / 256, iG / 256, iB / 256));
			HBRUSH hOld = (HBRUSH)SelectObject(pDC, hbr);
			FillRect(pDC, &rcx, hbr);
			DeleteObject(hbr);
			SelectObject(pDC, hOld);
		}

	}


	int in_test()
	{
		return 0;
	}
	typedef struct VERTEXUILISTPANEL
	{
		typedef int RUNFUN;
		std::vector<const wchar_t*>listtxt = { 128,(L"") };
		std::vector<int(*)()>listclick = { 128,(in_test) };
		COLORREF PanelBkColor = VERTEXUICOLOR_DARKNIGHT;

	}tagVertexUIList;

	typedef void (DRAWLISTPANEL)(HWND, HDC, VERTEXUILISTPANEL);
	void _VUIListPanel(HWND hWnd, HDC hdc, VERTEXUILISTPANEL vlp)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		int tsz = 40;
		CreateFillArea(hWnd, hdc, vlp.PanelBkColor);
		for (int i = 1; i <= 128; i++)
		{
			if (vlp.listtxt[i] == L"")
			{
				break;
			}

			CreateRect(hWnd, hdc, 40, i * 60 + tsz, 512, 40, VERTEXUICOLOR_MIDNIGHTPLUS);
			TextPreDrawEx(hdc, 50, i * 60 + tsz + 5, 512, 24, vlp.listtxt[i], 20, 0, VERTEXUICOLOR_WHITE);
		}
		CreateRect(hWnd, hdc, 1, tsz, rc.right - rc.left, 40, RGB(30, 35, 44));
		CreateSimpleButtonEx(hWnd, hdc, 1, tsz, 40, 40, VERTEXUICOLOR_GREENSEA, L"<", 30);
	}
	tagVertexUIList VertexUIList;
	void _CreateListPanel(HWND h, HDC hdc, VERTEXUILISTPANEL vlp, DRAWPANEL exDraw = 0)
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

		_VUIListPanel(h, hMemDC, vlp);
		if (exDraw != 0)
		{
			exDraw(h, hMemDC);
		}
		BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);


		SelectObject(hMemDC, hPreBmp);


		DeleteObject(hBmpMem);

		DeleteDC(hMemDC);
	}
	int _CreateListPanelAnimation(HWND h, HDC hdc, VERTEXUILISTPANEL vlp, DRAWPANEL exDraw = 0)
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
		_VUIListPanel(h, hMemDC, vlp);
		if (exDraw != 0)
		{
			exDraw(h, hMemDC);
		}

		if (anistat == 1)
		{
			BitBlt(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, SRCCOPY);
			anistat = 0;
			return -1;
		}
		if (anistat == 0)
		{
			BLENDFUNCTION bf = { 0 };
			bf.BlendOp = AC_SRC_OVER;
			bf.BlendFlags = 0;
			bf.SourceConstantAlpha = 1;
			bf.AlphaFormat = 0;
			Sleep(10);
			bf.SourceConstantAlpha = 10;
			AlphaBlend(hdc, 40, 40, rc.right - rc.left - 40 * 2, rc.bottom - rc.top - 40 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 20;
			AlphaBlend(hdc, 35, 35, rc.right - rc.left - 35 * 2, rc.bottom - rc.top - 35 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 30;
			AlphaBlend(hdc, 30, 30, rc.right - rc.left - 30 * 2, rc.bottom - rc.top - 30 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 40;
			AlphaBlend(hdc, 25, 25, rc.right - rc.left - 25 * 2, rc.bottom - rc.top - 25 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 55;
			AlphaBlend(hdc, 20, 20, rc.right - rc.left - 20 * 2, rc.bottom - rc.top - 20 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 67;
			AlphaBlend(hdc, 16, 16, rc.right - rc.left - 16 * 2, rc.bottom - rc.top - 16 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 91;
			AlphaBlend(hdc, 13, 13, rc.right - rc.left - 13 * 2, rc.bottom - rc.top - 13 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 110;
			AlphaBlend(hdc, 10, 10, rc.right - rc.left - 10 * 2, rc.bottom - rc.top - 10 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 150;
			AlphaBlend(hdc, 7, 7, rc.right - rc.left - 7 * 2, rc.bottom - rc.top - 7 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 210;
			AlphaBlend(hdc, 5, 5, rc.right - rc.left - 5 * 2, rc.bottom - rc.top - 5 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 230;
			AlphaBlend(hdc, 3, 3, rc.right - rc.left - 3 * 2, rc.bottom - rc.top - 3 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 240;
			AlphaBlend(hdc, 2, 2, rc.right - rc.left - 2 * 2, rc.bottom - rc.top - 2 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 249;
			AlphaBlend(hdc, 1, 1, rc.right - rc.left - 1 * 2, rc.bottom - rc.top - 1 * 2, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			Sleep(10);
			bf.SourceConstantAlpha = 255;
			AlphaBlend(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hMemDC, 0, 0, rc.right - rc.left, rc.bottom - rc.top, bf);
			anistat = 1;
			return -1;
		}

		SelectObject(hMemDC, hPreBmp);


		DeleteObject(hBmpMem);

		DeleteDC(hMemDC);

		return 0;
	}

	void CreateListPanel(HWND h, VERTEXUILISTPANEL vlp)
	{
		VertexUIList = {};
		VertexUIList = vlp;
		SwitchPanel(ListPanel);
	}
	void CreateListPanelByFlag(HWND h, HDC hdc, VERTEXUILISTPANEL vlp, DRAWPANEL DrawFun, int Flag = 0)
	{

		//On hMemDC.
		if (PanelID == PrevPanelID)
		{
			_CreateListPanel(h, hdc, vlp, DrawFun);
			anistat = 0;
		}
		if (PanelID != PrevPanelID)
		{
			if (Flag == 0)
			{
				_CreateListPanelAnimation(h, hdc, vlp, DrawFun);
			}
			if (Flag == 1)
			{
				_CreateListPanel(h, hdc, vlp, DrawFun);
			}
			PrevPanelID = PanelID;
			anistat = 0;
		}
	}
#define ListPanelEvent \
if (PanelID == ListPanel)\
{\
	RECT rc;\
	for (int i = 1; i <= 128; i++)\
	{\
\
		int tsz = 40;\
		if (VertexUIList.listtxt[i] == L"")\
		{\
			break;\
		}\
		AddBoxClickArea_Animation(hWnd, lParam, 40, i * 60 + tsz, 512, 40, VertexUIList.listclick[i])\
\
	}\
	TitleBarEvent \
AddBoxClickArea(hWnd,lParam,1,40,40,40,GoPagePrev)\
else\
{\
	if (hState == 1)\
	{\
		hState = 0;\
		RECT winrc2;\
		GetClientRect(hWnd, &winrc2);\
		InvalidateRect(hWnd, &winrc2, 0);\
		return 0;\
	}\
}\
\
}\

}

#ifdef VERTEXUI_DEVMODE
using namespace::VertexUI;
using namespace::VertexUI::Panel;

//Other


#endif

#ifdef test
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
#endif
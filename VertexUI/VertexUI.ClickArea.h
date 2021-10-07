#pragma once
/*
* VertexUI ClickArea
* 
* By EnderMo,VertexStudio 2021
* 
*/
#include "framework.h"
#include "VertexUI.Panel.h"
#include <stdio.h>
typedef int RUNFUN;

namespace VertexUI 
{
    namespace Click
    {
        using namespace::VertexUI::Panel;
        typedef struct VERTEXUIMOUSEEVENT
        {
            UINT hindex = 0;
            UINT phindex = 0;
        }VUIMOUSEEVENT,*PVUIMOUSEEVENT;
        VUIMOUSEEVENT vev;
        int ClickMsg = 0;
        int ClickArea(HWND hWnd, int x, int y, int sizex, int sizey, LPARAM lParam, RUNFUN function())
        {
            POINT pt;
            wchar_t txt[80];
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            wsprintf(txt, L"x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
            OutputDebugString(txt);
            RECT rect;
            GetClientRect(hWnd, &rect);
            RECT  rc = { x,y,x + sizex,y + sizey };
            if (PtInRect(&rc, pt))
            {
                function();
                return -1;
            }
            return -1;
        }


        int _ClickArea(HWND hWnd, RECT rc, LPARAM lParam, RUNFUN function())
        {
            POINT pt;
            wchar_t txt[80];
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            wsprintf(txt, L"x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
            OutputDebugString(txt);
            RECT rect;
            GetClientRect(hWnd, &rect);
            if (PtInRect(&rc, pt))
            {
                function();
                return -1;
            }
            return -1;
        }

        int ClickAreaEx(HWND hWnd, int x, int y, int sizex, int sizey, LPARAM lParam, RUNFUN function(),int msg)
        {
            POINT pt;
            wchar_t txt[80];
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            wsprintf(txt, L"x=%d;y=%d\n", LOWORD(lParam), HIWORD(lParam));
            OutputDebugString(txt);
            RECT rect;
            GetClientRect(hWnd, &rect);
            RECT  rc = { x,y,x + sizex,y + sizey };
            if (PtInRect(&rc, pt))
            {
                if (msg == 1)
                {
                    function();
                    return 0;
                }
                if (msg == 0)
                {
                    return -1;
                }
                else
                {
                    return -1;
                }
                return -1;
            }
            return -1;
        }
        int ClickAreaPtInfo(HWND hWnd, int x, int y, int sizex, int sizey, LPARAM lParam,int &value)
        {
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            RECT rect;
            GetClientRect(hWnd, &rect);
            RECT  rc = { x,y,x + sizex,y + sizey };
            if (PtInRect(&rc, pt))
            {
                value = 1;
                return -1;
            }
            else
            {
                value = 0;
                return -1;
            }
            return -1;
        }
        int GetAreaPtInfo(HWND hWnd, int x, int y, int sizex, int sizey, RECT& rc2, LPARAM lParam)
        {
            POINT pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            RECT rect;
            GetClientRect(hWnd, &rect);
            RECT  rc = { x,y,x + sizex,y + sizey };
            rc2 = { x,y,x + sizex,y + sizey };
            if (PtInRect(&rc, pt))
            {
                return 1;
            }
            else
            {
                return 0;
            }
            return -1;
        }
        int _CreateClickEvent(HWND hWnd, int x, int y, int sizex, int sizey, LPARAM lParam, RUNFUN function(), int msg)
        {
            ClickAreaEx(hWnd, x, y, sizex, sizey, lParam, function, msg);
            return 0;
        }

        int CreateClickEvent(HWND hWnd, int x, int y, int sizex, int sizey, LPARAM lParam, RUNFUN function(),  const wchar_t* Panelid)
        {
            int msg = 0;
            if (Panelid == PanelID)
            {
                msg = 1;
            }
            if (Panelid == PrevPanelID)
            {
                msg = 1;
            }

            else
            {
                msg = 0;
            }
            ClickAreaEx(hWnd, x, y, sizex, sizey, lParam, function, msg);
            return 0;
        }

       

        void SnedClickEvent(HWND hWnd,WPARAM w,LPARAM l)
        {
            ClickMsg = 1;
            SendMessage(hWnd, WM_MOUSEMOVE, w, l);
            ClickMsg = 0;
        }
    }
}

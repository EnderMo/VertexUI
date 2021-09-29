#pragma once
/*
* VertexUI ClickArea
* 
* By EnderMo,VertexStudio 2021
* 
*/
#include "framework.h"
#include "VertexUI.Panel.h"
typedef int RUNFUN;

namespace VertexUI 
{
    namespace Click
    {
        using namespace::VertexUI::Panel;
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
    }
}
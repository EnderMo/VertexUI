#pragma once
#include "framework.h"
BYTE Alpha = 255;
void   CALLBACK   TimerProc(HWND   hwnd, UINT   uMsg, UINT_PTR   idEvent, DWORD   dwTime)
{
    //BYTE Alpha = 255;
    Alpha -= 5;
    SetWindowLongPtr(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, Alpha, LWA_ALPHA);
    if (Alpha < 5)
    {
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
    }
}

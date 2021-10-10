# VertexUI
一个用于C++Win32桌面的简单界面API,正在开发<br>
本UI库使用windowless框架,使用GDI(利用其轻的特点)作为绘图底层,目前已经完成封装双缓冲和抗锯齿.<br>
<br>
### 用法 ###
请先创建一个Windows应用程序,并包含VertexUI界面库.
```C++
#include "VertexUI/VertexUI.min.h"
VertexUIInit;
```
在开始之前,请先在WM_CREATE中传出hWnd.
```C++
HWND GhWnd;
case WM_CREATE:
{
GhWnd = hWnd;
}
```
VertexUI用Panel(面板)来定义界面,每一个Panel的点击域都是不同的,界面也是不同的,同时,Panel需要您自己创建.
```C++
void Panel1(HWND hWnd, HDC hdc)
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    CreateFillArea(hWnd, hdc, RGB(20, 20, 20));//填充整个窗口 
    CreateSimpleButton(hWnd, hdc, rc.left + 40, rc.top + 40, 140, 40, L"按钮");
}
void Panel2(HWND hWnd, HDC hdc)
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    CreateFillArea(hWnd, hdc, VERTEXUICOLOR_DARKNIGHT);
    TextPreDrawEx(hdc, 0, 0, rc.right - rc.left, rc.bottom - rc.top, L"文本", 40, 1, VERTEXUICOLOR_WHITE);
    CreateSimpleButton(hWnd, hdc, rc.right - 170, rc.bottom - 80, 150, 40, L"返回");
}
```
同时,您需要为每一个按钮做好鼠标事件,一般这会在WM_MOUSEMOVE中实现,(如果您不需要hover,可以在WM_LBUTTONUP中调用ClickAreaEx,但我不建议这么做.)<br>
使用SwitchPanel来切换面板.
```C++
RUNFUN Button2()
{
    SwitchPanel(L"Panel2");
    return 0;
}
RUNFUN Button1()
{
    SwitchPanel(L"Panel2");
    return 0;
}
//鼠标事件
int hState = 0;
int AreaEvent(HWND hWnd, LPARAM lParam)
{

    int val = 0;
    RECT winrc;
    GetClientRect(hWnd, &winrc);

    if (PanelID == L"Init" || PanelID == L"Panel1")
    {
        RECT rc = {};
        if ((GetAreaPtInfo(hWnd, rc.left + 40, rc.top + 40, 140, 40, rc, lParam)) == 1)
        {
            if (ClickMsg == 1)
            {
                ClickMsg = 0;
                Button1();
            }
            if (hState == 0)
            {
                HDC hdc = GetDC(hWnd);
                CreateRect(hWnd, hdc, rc.left, rc.bottom - 5, rc.right - rc.left, 5, VERTEXUICOLOR_GREENDEEPSEA);
                DeleteObject(hdc);
                ReleaseDC(hWnd, hdc);
                DeleteDC(hdc);
                hState = 1;
            }
            return 0;
        }
        else
        {
            if (hState == 1)
            {
                hState = 0;
                InvalidateRect(hWnd, &winrc, 0);
            }
            return 0;
        }
    }
    if (PanelID == L"Panel2")
    {
        RECT rc = {};
        if ((GetAreaPtInfo(hWnd, winrc.right - 170, winrc.bottom - 80, 150, 40, rc, lParam)) == 1)
        {
            if (ClickMsg == 1)
            {
                ClickMsg = 0;
                Button2();
            }
            if (hState == 0)
            {
                HDC hdc = GetDC(hWnd);
                //CreateRect(hWnd, hdc, x, rc.bottom - 2, rc.right - rc.left, 2, VERTEXUICOLOR_GREENDEEPSEA);
                CreateRect(hWnd, hdc, rc.left, rc.bottom - 5, rc.right - rc.left, 5, VERTEXUICOLOR_GREENDEEPSEA);
                DeleteObject(hdc);
                ReleaseDC(hWnd, hdc);
                DeleteDC(hdc);
                hState = 1;
            }
            return 0;
        }
        else
        {
            if (hState == 1)
            {
                hState = 0;
                InvalidateRect(hWnd, &winrc, 0);
                return 0;
            }
        }
    }
    if (PanelID != 0)
    {

    }

    return 0;
}
//WndProc中
    case WM_MOUSEMOVE:
    {
        AreaEvent(hWnd, lParam);
        break;
    }
    case WM_ERASEBKGND:
    {
        break;
    }
    case WM_LBUTTONUP:
    {
        SnedClickEvent(hWnd, wParam, lParam); //发送Click,mousemove检测ClickMsg
        return 0;
    }
```
现在,总体布置已经ok啦!最后一步,只需要在WM_PAINT中相应每一个Panel的绘制就好啦!
```C++
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // 切换
        if (PanelID == L"Init")
        {
            CreatePanelByFlag(hWnd, hdc, Panel1);
        }
        if (PanelID == L"Panel2")
        {
            CreatePanelByFlag(hWnd, hdc, Panel2);
        }
        EndPaint(hWnd, &ps);
        break;
    }
```
### 感谢使用VertexUI. ###

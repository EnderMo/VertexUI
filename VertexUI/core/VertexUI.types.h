#pragma once
//关于事件的回调规范
struct WindowConfig{
    #ifdef __linux__
    //这里可以存放窗口管理需要用到的一些东西qwq
    Window window;
    Display *display;
    XEvent xevent;
    int screen_index;



    #elif _WIN32

    #endif
};
enum class VUIEvent{
    MouseClicked,
};
//typedef void (*OnMouseEvent) (int x,int y,MouseEvent);                          //鼠标事件
//typedef void (*OnPaint) ();

struct CallBackEvent
{

    /* data */
};


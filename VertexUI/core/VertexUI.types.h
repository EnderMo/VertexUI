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
    //这里就是windows窗口需要放的东西了啦

    #endif
};
struct VPoint{
    int x,y;
};              //点

enum class VUIEvent{
    MouseClicked,
};
typedef void (*OnMouseClicked) (VPoint posizion);                          //鼠标点击时间
typedef void (*OnPaint) ();

struct CallBackEvent
{

    /* data */
};


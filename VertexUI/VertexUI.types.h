#pragma once
#include "VertexUI.min.h"
//关于事件的回调规范
enum class MouseEvent{
    Click,Release
};
typedef void (*OnMouseEvent) (int x,int y,MouseEvent);                          //鼠标事件
typedef void (*OnPaint) ();

struct CallBackEvent
{

    /* data */
};


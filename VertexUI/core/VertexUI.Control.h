#pragma once
#include "VertexUI.VObject.h"
class VControl:VObject{
#ifdef __linux__

#elif _WIN32



#endif
public:
    int x,y;                //控件的位置
    int width,height;       //控件的高度和宽度
            


    //下面是一堆消息函数
    std::vector<OnMouseClicked*> OnMouseClickedFuncions;
private:
    std::vector<VControl*> Children;
    virtual void OnPaint();
    
    void EventReceiver(VUIEvent event,void* data);                 //用于向下传递消息，并以此调用组件内部的消息接受







};

#include "VertexUI.Control.h"

void VControl::EventReceiver(VUIEvent event,void * data){
    //如果是鼠标等具有位置信息的事件，先判断此事件是否与自己相关
    if (event==VUIEvent::MouseClicked){
        if(!(((VPoint*)data)->x>this->x||
        ((VPoint*)data)->x<(this->x+this->width)||
        ((VPoint*)data)->y>this->y||
        ((VPoint*)data)->y<(this->x+this->height))){
            return;
            //鼠标事件不在区域内，退出

        }
    }
    switch (event){
        case VUIEvent::MouseClicked:
            for (auto i:this->OnMouseClickedFuncions){
                *i();
            }
            break;
        
    }

}
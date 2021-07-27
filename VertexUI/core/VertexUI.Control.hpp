#pragma once
#include "VertexUI.VObject.h"
#include 
class VControl:VObject{
#ifdef __linux__

#elif _WIN32

#else


#endif
public:
    
private:
    virtual void OnPaint();
    
    template<class T>
    void EventReceiver(VUIEvent event,T* data);                 //用于向下传递消息







};

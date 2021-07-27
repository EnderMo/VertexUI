#pragma once
#include "VertexUI.VObject.h"
class VControl:VObject{
#ifdef __linux__

#elif _WIN32

#else


#endif
public:
    
private:
    std::vector<VControl*> Children;
    virtual void OnPaint();
    
    template<class T>
    void EventReceiver(VUIEvent event,T* data);                 //用于向下传递消息







};

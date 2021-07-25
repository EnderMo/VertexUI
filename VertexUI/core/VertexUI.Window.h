#pragma once
#include "framework.h"
#include "VertexUI.VObject.h"

class Window:VObject{
#ifdef __linux__
private:
    //窗口信息
    //Linux代码放在这
#elif _WIN32
    // Windows代码放在这
#else
    //本gui库不支持其他的牛马系统
#endif
    //通用代码放这
private:
    std::vector<VObject*> Children;                                                                         //实现子组件管理
public:
    
    int EventLoop();                                                                                                    //窗体消息循环

};

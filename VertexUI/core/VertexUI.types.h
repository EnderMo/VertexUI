#pragma once
#include "framework.h"
#include "VertexUI.VObject.h"
class Window
{
#ifdef __linux__
private:
    std::vector<VObject*> Children;
    //Linux代码放在这
#elif _WIN32
    // Windows代码放在这
#else
    //本gui库不支持其他的牛马系统
#endif
};
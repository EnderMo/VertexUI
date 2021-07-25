#pragma once
#include "VertexUI.Control.h"
//这是最基本的控件
class VUIPanel
{
private:
    
public:
    VUIPanel();
    VUIPanel(VControl* Parent);                     //通过指定父级来构建
    ~VUIPanel();
};

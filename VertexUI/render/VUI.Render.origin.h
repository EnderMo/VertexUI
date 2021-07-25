#pragma once
class VUI_Render_ORIGIN{
    virtual void DrewRect(int x,int y,int width,int height)=0;


    VUI_Render_ORIGIN();
    ~VUI_Render_ORIGIN();
    

}
//这里定义了Render的基本格式
//在其他平台的文件中，只需要把这个类中所有的虚函数实现就好
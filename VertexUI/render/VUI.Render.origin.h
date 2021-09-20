#pragma once
#include "../../framework.h"

class VUIColor
{
private:
    int cr, cg, cb;
    float ca;

public:
    inline VUIColor(int r, int g, int b, float a = 1){
        this->ca = a;
        this->cr = r;
        this->cb = b;
        this->cg = g;
    }
    inline VUIColor(const char *hexColor){
        switch (strlen(hexColor))
        {

        case 7:
        //格式#ffffff

            char *dest=new char[6];
            memcpy(dest,hexColor+1,7);
            this->cr=std::stoi(std::string(dest).substr(0,2),0,16);
            this->cg=std::stoi(std::string(dest).substr(2,2),0,16);
            this->cb=std::stoi(std::string(dest).substr(4,2),0,16);
            break;
        case 9:
        //格式#ffffffff
            char *dest=new char[8];
            memcpy (dest,hexColor+1,8);
             this->cr=std::stoi(std::string(dest).substr(0,2),0,16);
            this->cg=std::stoi(std::string(dest).substr(2,2),0,16);
            this->cb=std::stoi(std::string(dest).substr(4,2),0,16);
            this->ca=std::stoi(std::string(dest).substr(6,2),0,16)/256;

            break;
        default:
            this->ca = 0;
            this->cr =0;
            this->cb = 0;
            this->cg = 0;

        }

    }
    inline ~VUIColor() {}
};

class VUI_Render_ORIGIN{
    virtual void DrewRect(int x, int y, int width, int height) = 0;
    virtual void PutPixel(int x, int y) = 0;
    //Render需要绑定主窗口的画布，不同系统的画布不一样，比如windows的GDI就是HDC
    virtual void bind() = 0; //linux

    VUI_Render_ORIGIN();
    ~VUI_Render_ORIGIN();
};

//这里定义了Render的基本格式
//在其他平台的文件中，只需要把这个类中所有的虚函数实现就好




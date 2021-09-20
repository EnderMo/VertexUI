#include "VertexUI.Window.h"
VUIWindow::VUIWindow(int x, int y, int width, int height)
{
#ifdef __linux__
    //Linux创建窗体代码放在此处
    
    //创建窗体
    this->config.display = XOpenDisplay(NULL);
    if (this->config.display == NULL)
    {
        std::cout << "Cannot open display" << std::endl;
        exit(-1);
    }
    this->config.screen_index = DefaultScreen(this->config.display);
    this->config.window = XCreateSimpleWindow(config.display,
                                              RootWindow(config.display, config.screen_index),
                                              x,
                                              y,
                                              width,
                                              height,
                                              0,
                                              BlackPixel(config.display, config.screen_index),
                                              WhitePixel(config.display, config.screen_index));
    

#elif _WIN32
    //这个地方放置windows创建窗体的代码    

#endif
}
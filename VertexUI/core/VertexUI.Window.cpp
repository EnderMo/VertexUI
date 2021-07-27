#include "VertexUI.Window.h"
VUIWindow::VUIWindow(int x, int y, int width, int height)
{
#ifdef __linux__
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

#endif
}
#include "VUI.Render.origin.h"

//按照编译环境引入不同的Render实现
#ifdef __linux__ 
#include "VUI.Render.linux.hpp"
#elif _WIN32
#include "VUI.Render.windows.h"
#else
#endif



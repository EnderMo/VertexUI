/*
* framework.h
* 
* 包含WINAPI运行库,同时包含VertexUI预处理宏


(添加了linux的预编译处理)
*/

#pragma once


// C 运行时头文件
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <memory.h>
//C++ 官方库
#include <bits/stdc++.h>
#ifdef __linux__ 
    //Linux代码放在这
#include <X11/Xlib.h>
#elif _WIN32
    // Windows代码放在这
 #include "targetver.h"
#include <tchar.h>
#include <windows.h>
// Windows 头文件

#else
    //本gui库不支持其他的牛马系统

#endif






#define SimpleCode //更简洁的代码

//#define VertexUI_LightMode  //明亮模式
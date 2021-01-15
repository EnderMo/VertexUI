/*
* framework.h
* 
* 包含WINAPI运行库,同时包含VertexUI预处理宏
*/

#pragma once

#include "targetver.h"
// Windows 头文件
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#define SimpleCode //更简洁的代码

//#define VertexUI_LightMode  //明亮模式
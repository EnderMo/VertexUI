#pragma once
#ifndef _VERTEXUI_HLE_CONTROL_H
#define _VERTEXUI_HLE_CONTROL_H

#include <Windows.h>

namespace VertexUI::Hle
{
    class Control
    {
    public:
        Control() : Control(nullptr) {}
        Control(HWND window) { GetClientRect(window, &rc_); }
        Control(RECT rc) : rc_(rc) {}

        virtual ~Control() {}

        virtual void Create(HWND window, HDC dc) = 0;

        RECT GetRect() { return rc_; }

    protected:
        RECT rc_;

        void SetRect_(RECT rc)
        {
            SetRect_(rc.left, rc.right, rc.top, rc.bottom);
        }

        void SetRect_(int left, int right, int top, int bottom)
        {
            if (left < 0) rc_.left -= left; else rc_.left = left;
            if (right < 0) rc_.right -= right; else rc_.right = right;
            if (top < 0) rc_.top -= top; else rc_.top = top;
            if (bottom < 0) rc_.bottom -= bottom; else rc_.bottom = bottom;
            this;
        }
    };
}

#endif // !_VERTEXUI_HLE_CONTROL_H
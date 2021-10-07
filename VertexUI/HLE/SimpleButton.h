#pragma once
#ifndef _VERTEXUI_HLE_SIMPLEBUTTON_H_
#define _VERTEXUI_HLE_SIMPLEBUTTON_H_

#include "../VertexUI.Panel.h"
#include "Control.h"

namespace VertexUI::Hle
{
    class SimpleButton : public Control
    {
    public:
        // using Control<SimpleButton>::Control;
        wchar_t const* GetText() { return text_; }
        SimpleButton* SetText(wchar_t const* text) { text_ = text; return this; }

        SimpleButton* SetRect(RECT rc)
        {
            return SetRect(rc.left, rc.right, rc.top, rc.bottom);
        }

        SimpleButton* SetRect(int left, int right, int top, int bottom)
        {
            SetRect_(left, right, top, bottom);
            return this;
        }

        void Create(HWND window, HDC dc) override
        {
            CreateSimpleButton(window, dc, rc_.left, rc_.top, rc_.right, rc_.bottom, text_);
        }
    protected:
        wchar_t const* text_;
    };
}

#endif // !_VERTEXUI_HLE_SIMPLEBUTTON_H_
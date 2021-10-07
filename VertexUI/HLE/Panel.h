#pragma once
#ifndef _VERTEXUI_HLE_PANEL_H_
#define _VERTEXUI_HLE_PANEL_H_

#include <vector>
#include <Windows.h>
#include "../VertexUI.Panel.h"
#include "../VertexUI.ClickArea.h"
#include "Control.h"

namespace VertexUI::Hle
{
    class Panel;

    Panel* currentPanel{ nullptr };

    class Panel
    {
        const wchar_t* id_;
    public:
        template <typename... Args>
        Panel(const wchar_t* id, Args*... controls)
            : id_(id)
        {
            AddControl(controls...);
        }

        ~Panel()
        {
            for (auto&& control : controls_)
            {
                if (control)
                {
                    delete control;
                    control = nullptr;
                }
            }
        }

        void Create(HWND window, HDC dc)
        {
            currentPanel = this;
            CreatePanelByFlag(window, dc, Panel::DrawPanel);
        }

        void MouseMove(HWND window, LPARAM lParam)
        {
            for (auto control : controls_)
            {
                RECT rc = control->GetRect();
            }
        }

        void AddControl(Control* control) { controls_.push_back(control); }
        template <typename Arg, typename... Args>
        void AddControls(Arg control, Args*... controls)
        {
            AddControl(control);
            if constexpr (sizeof...(controls) > 0)
                AddControls(controls...);
        }

        static void DrawPanel(HWND window, HDC dc)
        {
            CreateFillArea(window, dc, RGB(42, 47, 56));
            for (auto control : currentPanel->controls_)
                control->Create(window, dc);
        }
    protected:
        std::vector<Control*> controls_;
    };
}

#endif // !_VERTEXUI_HLE_PANEL_H_
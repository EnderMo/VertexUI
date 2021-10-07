#pragma once
#ifndef _VERTEXUI_HLE_APPLICATION_H_
#define _VERTEXUI_HLE_APPLICATION_H_

#include <map>
#include <functional>
#include <Windows.h>
#include "../VertexUI.Panel.h"
#include "../VertexUI.ClickArea.h"
#include "Panel.h"

#define Main __entrypoint(int argc, wchar_t* argv[]);                             \
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {    \
  int arg_count{ 0 };                                                             \
  wchar_t** arg_list{ CommandLineToArgvW(GetCommandLineW(), &arg_count) };        \
  int ret = __entrypoint(arg_count, arg_list);                                    \
  if (arg_list != nullptr)                                                        \
    LocalFree(arg_list);                                                          \
  return ret;                                                                     \
}                                                                                 \
int __entrypoint

namespace VertexUI::Hle
{
    template <typename UpdateT, typename ModelT>
    class Application
    {
        using init_type = std::function<ModelT(void)>;
        using update_type = UpdateT;
        using view_type = std::function<Panel(ModelT&)>;

        init_type init_;
        update_type update_;
        view_type view_;
        ModelT model_;
        HINSTANCE instance_;
        HWND window_;
        std::map<const wchar_t*, Panel*> panels;
    public:
        Application(init_type init, view_type view)
            : init_(init), update_(update_type()), view_(view), model_(init())
        {
            Initialize();
        }

        void RunMessageLoop()
        {
            MSG msg;

            while (GetMessage(&msg, nullptr, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

    private:
        HRESULT Initialize()
        {
            instance_ = GetModuleHandle(nullptr);

            WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = Application::WindowProcess;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = sizeof(LONG_PTR);
            wcex.hInstance = instance_;
            wcex.hbrBackground = nullptr;
            wcex.lpszMenuName = nullptr;
            wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
            wcex.lpszClassName = L"VertexUIHLE";

            RegisterClassEx(&wcex);

            window_ = CreateWindowExW(
                0, L"VertexUIHLE", L"VertexUI Demo", WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                nullptr, nullptr, GetModuleHandle(nullptr), this);
            HRESULT hr = window_ ? S_OK : E_FAIL;
            if (SUCCEEDED(hr))
            {
                ShowWindow(window_, SW_SHOWNORMAL);
                UpdateWindow(window_);
            }

            return hr;
        }

        void Paint()
        {
            RECT winrc, rc;
            GetClientRect(window_, &rc);
            GetWindowRect(window_, &winrc);
            int scrWidth, scrHeight;
            scrWidth = GetSystemMetrics(SM_CXSCREEN);
            scrHeight = GetSystemMetrics(SM_CYSCREEN);
            if (winrc.top + (rc.bottom - rc.top) >= scrHeight ||
                winrc.left + (rc.right - rc.left) >= scrWidth ||
                winrc.left <= 0 || winrc.top <= 0)
                if (PanelID != PrevPanelID)
                    InvalidateRect(window_, &rc, 0);
                else return;
            PAINTSTRUCT ps;
            BeginPaint(window_, &ps);
            Panel panel = view_(model_);
            panel.Create(window_, ps.hdc);
            EndPaint(window_, &ps);
        }

        void AreaEvent()
        {
            if (PanelID == L"Init" || PanelID == L"Panel1")
            {

            }
        }

        static LRESULT CALLBACK WindowProcess(HWND window, unsigned message,
            WPARAM wParam, LPARAM lParam)
        {
            if (message == WM_CREATE)
            {
                auto cs = reinterpret_cast<LPCREATESTRUCT>(lParam);
                auto app = reinterpret_cast<Application*>(cs->lpCreateParams);

                ::SetWindowLongPtrW(
                    window,
                    GWLP_USERDATA,
                    reinterpret_cast<LONG_PTR>(app));

                return 1;
            }
            auto app = reinterpret_cast<Application*>(static_cast<long>(
                ::GetWindowLongPtrW(
                    window,
                    GWLP_USERDATA)));
            if (app)
                switch (message)
                {
                case WM_PAINT:
                    app->Paint();
                    return 0;
                case WM_DESTROY:
                    PostQuitMessage(0);
                    return 0;
                case WM_MOUSEMOVE:
                    app->AreaEvent();
                default:
                    return DefWindowProc(window, message, wParam, lParam);
                }
            return 1;
        }
    };
}

#endif // !_VERTEXUI_HLE_APPLICATION_H_
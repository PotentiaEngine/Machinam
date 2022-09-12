#include "EngineRuntime.h"
#include "engine/command/CommandAllocator.h"
#include "engine/devices/LogicalDevice.h"
#include "engine/surface/SwapChain.h"
#include "engine/surface/RenderTargetViews.h"
#include "engine/window/AppWindow.h"
#include "engine/command/CommandQueue.h"
#include <memory>

RECT EngineRuntime::m_windowRect = {};

EngineRuntime::EngineRuntime() : is_init(false) {}

int EngineRuntime::run(HINSTANCE hInstance, int nCmdShow) {
  int argc;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  LocalFree(argv);

  WNDCLASSEX windowClass = {0};
  windowClass.cbSize = sizeof(WNDCLASSEX);
  windowClass.style = CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc = WindowProc;
  windowClass.hInstance = hInstance;
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowClass.lpszClassName = "DXSampleClass";
  RegisterClassEx(&windowClass);

  m_windowRect = {0, 0, static_cast<LONG>(1500), static_cast<LONG>(1000)};
  AdjustWindowRect(&m_windowRect, c_windowStyle, FALSE);

  m_hwnd = CreateWindow(windowClass.lpszClassName, "Game", c_windowStyle,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        m_windowRect.right - m_windowRect.left,
                        m_windowRect.bottom - m_windowRect.top, nullptr,
                        nullptr, hInstance, NULL);
  

  is_init = true;
  
  AppWindow::Instance()->Assign(m_hwnd);
  LogicalDevice::Instance()->Create();
  CommandQueue::Instance()->Create();
  SwapChain::Instance()->Create();
  RenderTargetViews::Instance()->Create();
  CommandAllocator::Instance()->Create();

  ShowWindow(m_hwnd, true);

  MSG msg = {};
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_KEYDOWN) {
        PostMessage(m_hwnd, WM_CLOSE, 0, 0);
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
  return static_cast<char>(msg.wParam);
}

LRESULT CALLBACK EngineRuntime::WindowProc(HWND hWnd, UINT message,
                                           WPARAM wParam, LPARAM lParam) {
  switch (message) {
    case WM_CREATE: {
      LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
      SetWindowLongPtr(
          hWnd, GWLP_USERDATA,
          reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
    }
      return 0;
    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }
  }
  return DefWindowProc(hWnd, message, wParam, lParam);
}

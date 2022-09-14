#include "GameWindow.h"

void GameWindow::Init(HINSTANCE hInstance, int nCmdShow) {
  m_hInstance = hInstance;
  m_cmdShow = nCmdShow;
  InitWindow();
  CreateGameWindow();
}

void GameWindow::InitWindow() {
  WNDCLASSEX windowClass = {0};
  windowClass.cbSize = sizeof(WNDCLASSEX);
  windowClass.style = CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc = WindowProc;
  windowClass.hInstance = m_hInstance;
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowClass.lpszClassName = "PotentiaClass";

  RegisterClassEx(&windowClass);
  m_windowClass = windowClass;
}

LRESULT CALLBACK GameWindow::WindowProc(HWND hwnd, UINT message, WPARAM wParam,
                                        LPARAM lParam) {
  switch (message) {
  case WM_CREATE: {
    LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
    SetWindowLongPtr(hwnd, GWLP_USERDATA,
                     reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
  }
    return 0;
  }
  return DefWindowProc(hwnd, message, wParam, lParam);
}

void GameWindow::CreateGameWindow() {
  RECT windowRect = {0, 0, 1500, 1000};
  AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
  m_windowSize = {float(windowRect.right - windowRect.left), float(windowRect.bottom - windowRect.top)};
  m_handle = CreateWindow(m_windowClass.lpszClassName, "Game",
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                          windowRect.right - windowRect.left,
                          windowRect.bottom - windowRect.top, nullptr, nullptr,
                          m_hInstance, NULL);
}

void GameWindow::Show() {
  ShowWindow(m_handle, m_cmdShow);
}

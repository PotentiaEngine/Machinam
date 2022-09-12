#pragma once

#include "pch.h"

class EngineRuntime {
 public:
  EngineRuntime();
  int run(HINSTANCE hInstance, int nCmdShow);

 protected:
  static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                                     LPARAM lParam);
  static const LONG c_windowStyle = WS_OVERLAPPEDWINDOW;
  HWND m_hwnd;
  static RECT m_windowRect;

 private:
  bool is_init;
};

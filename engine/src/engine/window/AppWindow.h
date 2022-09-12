#pragma once

#include "pch.h"
#include "engine/base/Singleton.h"
#include <winuser.h>

class AppWindow : public Singleton<AppWindow>{

public:
  void Assign(HWND handle);  
  void SetTitle(LPCSTR title);
  void SetSize(RECT rect);
  Getter(XMFLOAT2, WindowSize, m_windowSize);
  Getter(HWND, RawHandle, m_handle);
protected:
  HWND m_handle;
  XMFLOAT2 m_windowSize;
  static const DWORD c_windowStyle = WS_OVERLAPPEDWINDOW;
};

#pragma once
#include "core/EngineCore.h"
#include "core/base/Singleton.h"
#include <DirectXMath.h>

class GameWindow : public Singleton<GameWindow> {
  public:
    void Init(HINSTANCE hInstance, int nCmdShow);
    void Show();
    XMFLOAT2 GetWindowSize() const {return m_windowSize;}
    HWND GetRawHandle() const {return m_handle; }
  protected:
    HWND m_handle;
    HINSTANCE m_hInstance;
    int m_cmdShow;
    WNDCLASSEX m_windowClass;
    XMFLOAT2 m_windowSize;
    void InitWindow();
    void CreateGameWindow();
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
};

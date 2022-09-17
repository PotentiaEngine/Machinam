#pragma once
#include "core/EngineCore.h"
#include "core/base/Singleton.h"
#include "core/d3dx12.h"
#include <DirectXMath.h>

class GameWindow : public Singleton<GameWindow> {
  public:
    void Init(HINSTANCE hInstance, int nCmdShow);
    void Show();
    XMFLOAT2 GetWindowSize() const {return m_windowSize;}
    HWND GetRawHandle() const {return m_handle; }
    CD3DX12_VIEWPORT GetViewport() { return CD3DX12_VIEWPORT(0.f, 0.f, m_windowSize.x, m_windowSize.y); };
    CD3DX12_RECT GetScissorRect() {return CD3DX12_RECT(0.f, 0.f, m_windowSize.x, m_windowSize.y);};
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

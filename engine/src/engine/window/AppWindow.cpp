#include "AppWindow.h"
#include <winuser.h>


void AppWindow::Assign(HWND handle) {
  RECT size;
  GetClientRect(handle, &size);
  SetSize(size);
  m_handle = handle;
}

void AppWindow::SetSize(RECT rect) {
  m_windowSize.x = rect.right - rect.left;
  m_windowSize.y = rect.bottom - rect.top;
  AdjustWindowRect(&rect, c_windowStyle, FALSE);
}

void AppWindow::SetTitle(LPCSTR title) {
  SetWindowText(m_handle, title);
}

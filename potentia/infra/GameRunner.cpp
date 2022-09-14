#include "GameRunner.h"

#include "infra/command/CommandAllocator.h"
#include "infra/command/CommandQueue.h"
#include "infra/devices/LogicalDevice.h"
#include "infra/surface/RenderTargetViews.h"
#include "infra/surface/SwapChain.h"
#include <winuser.h>

void GameRunner::InitWithWindow(Shared(GameWindow) window) {
  LogicalDevice::Get()->Create();
  CommandQueue::Get()->Create();
  SwapChain::Get()->Create();
  RenderTargetViews::Get()->Create();
  CommandAllocator::Get()->Create();
  window->Show();
}

void GameRunner::Run() {
  MSG msg = {};
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_KEYDOWN) {
        // Engine Behaviour global functionality for engine whilst being
        // component-like system
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

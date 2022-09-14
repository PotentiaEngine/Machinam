#include "GameRunner.h"

#include "infra/command/CommandAllocator.h"
#include "infra/command/CommandQueue.h"
#include "infra/devices/LogicalDevice.h"
#include "infra/surface/RenderTargetViews.h"
#include "infra/surface/SwapChain.h"
#include <winuser.h>

#define EBRun(game, call) game->GetEngineBehaviourRegistry()->RunForAll(std::function([](Shared(EngineBehaviour) b) { call; }))

void GameRunner::InitWithWindow(Shared(GameInstance) game) {
  LogicalDevice::Get()->Create();
  CommandQueue::Get()->Create();
  SwapChain::Get()->Create();
  RenderTargetViews::Get()->Create();
  CommandAllocator::Get()->Create();
  GameWindow::Get()->Show();
  m_game = game;
}

void GameRunner::Run() {
  MSG msg = {};
  while (msg.message != WM_QUIT) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      
      EBRun(m_game, b->Update()); 

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

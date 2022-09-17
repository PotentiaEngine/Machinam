#include "GameRunner.h"

#include "infra/command/CommandAllocator.h"
#include "infra/command/CommandQueue.h"
#include "infra/devices/LogicalDevice.h"
#include "infra/surface/RenderTargetViews.h"
#include "infra/surface/SwapChain.h"
#include "infra/surface/SynchronisationController.h"
#include "structure/pipeline/GraphicsPipeline.h"
#include <winuser.h>

#define EBRun(game, call)                                                      \
  game->GetEngineBehaviourRegistry()->RunForAll(                               \
      std::function([](Shared(EngineBehaviour) b) { call; }))

void GameRunner::InitWithWindow(Shared(GameInstance) game) {
  m_game = game;
  LogicalDevice::Get()->Create();
  CommandQueue::Get()->Create();
  SwapChain::Get()->Create();
  RenderTargetViews::Get()->Create();
  CommandAllocator::Get()->Create();
  GameWindow::Get()->Show();
  SynchronisationController::Get()->Create();
  game->RegisterRoot();
  game->GetGraphicsPipelines()->RunForAll(
      std::function([](Shared(GraphicsPipeline) p) { p->Setup(); }));
}

void GameRunner::Run() {
  MSG msg = {};
  while (msg.message != WM_QUIT) {

    m_game->Render();
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }
}

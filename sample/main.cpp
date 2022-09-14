#include "SampleGame.h"
#include "core/EngineCore.h"
#include "core/macros.h"
#include "infra/GameRunner.h"
#include "infra/window/GameWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE previousHInstance,
                   PWSTR pCmdLine, int nCmdLine) {
  GameWindow::Get()->Init(hInstance, nCmdLine);
  auto game = MakeShared(SampleGame);
  GameRunner::Get()->InitWithWindow(game);
  GameRunner::Get()->Run();
  return 0;
}

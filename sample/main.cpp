#include "SampleGame.h"
#include <potentia/core/EngineCore.h>
#include <potentia/core/macros.h>
#include <potentia/infra/GameRunner.h>
#include <potentia/infra/window/GameWindow.h>


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE previousHInstance,
                   PWSTR pCmdLine, int nCmdLine) {
  GameWindow::Get()->Init(hInstance, nCmdLine);
  auto game = MakeShared(SampleGame);
  GameRunner::Get()->InitWithWindow(game);
  GameRunner::Get()->Run();
  return 0;
}

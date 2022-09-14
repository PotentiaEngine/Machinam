#include "core/EngineCore.h"
#include "infra/GameRunner.h"
#include "infra/window/GameWindow.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE previousHInstance,
                   PWSTR pCmdLine, int nCmdLine) {
  GameWindow::Get()->Init(hInstance, nCmdLine);
  GameRunner::Get()->InitWithWindow(GameWindow::Get());
  GameRunner::Get()->Run();
  return 0;
}

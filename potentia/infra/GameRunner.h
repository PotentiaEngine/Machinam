#pragma once

#include "core/EngineCore.h"
#include "core/base/Singleton.h"
#include "window/GameWindow.h"


class GameRunner : public Singleton<GameRunner> {
  public:
    void InitWithWindow(Shared(GameWindow) window);
    void Run();
};

#pragma once

#include "core/EngineCore.h"
#include "core/base/Singleton.h"
#include "structure/GameInstance.h"
#include "window/GameWindow.h"


class GameRunner : public Singleton<GameRunner> {
  public:
    void InitWithWindow(Shared(GameInstance) game);
    void Run();
  private:
    Shared(GameInstance) m_game;
};

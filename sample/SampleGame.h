#pragma once

#include <potentia/structure/GameInstance.h>

class SampleGame : public GameInstance {
  public:
    SampleGame();

    void RegisterRoot() override;
};

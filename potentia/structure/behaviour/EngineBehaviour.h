#pragma once

#include "core/EngineCore.h"
#include "structure/base/Behaviour.h"
#include <optional>

class EngineBehaviour : public Behaviour {
  public:
    void SetMessage(MSG msg);
    void Update() override;

  protected:
    virtual void ProcessTick(MSG message) = 0;
  private:
    std::optional<MSG> m_msg;
};

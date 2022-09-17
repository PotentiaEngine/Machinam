#pragma once

#include "core/EngineCore.h"
#include "structure/Registry.h"
#include "structure/base/Behaviour.h"
#include <vector>

class ComponentActor : public Behaviour {
  protected:
    void AddBehaviour(Shared(Behaviour) behaviour);
    Shared(Registry<Behaviour>) m_behaviours;
};

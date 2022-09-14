#pragma once

#include "structure/base/Behaviour.h"
#include <functional>


template<class TBehaviour>
class BehaviourRegistry {
  public:
    void Register(Shared(TBehaviour) behaviour);
    void RunForAll(std::function<void(Shared(TBehaviour))> fn);
  private:
    std::vector<Shared(TBehaviour)> behaviours;
};


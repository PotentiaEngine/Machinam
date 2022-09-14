#pragma once

#include "core/EngineCore.h"
#include "Registry.h"
#include "infra/pipeline/PipelineState.h"
#include "structure/behaviour/EngineBehaviour.h"

class GameInstance {
public:
  GameInstance();
  // same for levels + assets
  Shared(Registry<EngineBehaviour>) GetEngineBehaviourRegistry() const {
    return m_engineBehaviours;
  };
  Shared(std::vector<Shared(PipelineState)>) GetAllPSOs() const {
    return m_psos;
  };

protected:
  virtual void RegisterRoot() {};
  
  void RegisterPSO(Shared(PipelineState));

  Shared(std::vector<Shared(PipelineState)>) m_psos;
  // same for levels + assets
  Shared(Registry<EngineBehaviour>) m_engineBehaviours;
};


#pragma once

#include "core/EngineCore.h"
#include "Registry.h"
#include "infra/pipeline/PipelineState.h"
#include "structure/behaviour/EngineBehaviour.h"
#include "structure/pipeline/GraphicsPipeline.h"

class GameInstance {
public:
  GameInstance();
  void Render();
  // same for levels + assets
  Shared(Registry<EngineBehaviour>) GetEngineBehaviourRegistry() const {
    return m_engineBehaviours;
  };

  Shared(Registry<GraphicsPipeline>) GetGraphicsPipelines() {
    return m_graphicsPipelines;
  }

  virtual void RegisterRoot() = 0;
  
  void RegisterPipeline(Shared(GraphicsPipeline) pipline) {
    m_graphicsPipelines->Register(pipline);
  }

  // same for levels + assets
  Shared(Registry<EngineBehaviour>) m_engineBehaviours;
  Shared(Registry<GraphicsPipeline>) m_graphicsPipelines;
};


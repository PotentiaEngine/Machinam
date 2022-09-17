#include "GameInstance.h"
#include "core/EngineCore.h"
#include "core/macros.h"
#include "infra/command/CommandAllocator.h"
#include "infra/pipeline/PipelineState.h"
#include "infra/surface/SwapChain.h"
#include "infra/surface/SynchronisationController.h"
#include "structure/Registry.h"
#include "structure/pipeline/GraphicsPipeline.h"


GameInstance::GameInstance() {
  m_engineBehaviours = MakeShared(Registry<EngineBehaviour>);
  m_graphicsPipelines = MakeShared(Registry<GraphicsPipeline>);
}


void GameInstance::Render() {
  ThrowOnFail(CommandAllocator::Get()->GetCommandAllocator().Reset());

  m_graphicsPipelines->RunForAll(std::function([](Shared(GraphicsPipeline) p) {p->RenderAll();}));
  SwapChain::Get()->GetSwapChain()->Present(1, 0);
  SynchronisationController::Get()->WaitForGPU();
}

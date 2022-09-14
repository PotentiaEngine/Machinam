#include "GameInstance.h"
#include "core/macros.h"
#include "infra/pipeline/PipelineState.h"
#include "structure/Registry.h"


GameInstance::GameInstance() {
  m_engineBehaviours = MakeShared(Registry<EngineBehaviour>);
  RegisterRoot();
}

void GameInstance::RegisterPSO(Shared(PipelineState) pso) {
  pso->Finalize();
  m_psos->push_back(pso);
}

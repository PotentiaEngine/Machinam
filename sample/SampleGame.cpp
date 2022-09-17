#include "SampleGame.h"
#include <potentia/core/macros.h>
#include <potentia/infra/pipeline/PipelineState.h>
#include <potentia/infra/pipeline/RootSignature.h>
#include <potentia/infra/pipeline/Shader.h>
#include <potentia/structure/GameInstance.h>
#include "pipelines/MainGfxPipeline.h"

SampleGame::SampleGame() {

}


void SampleGame::RegisterRoot() {
  auto main = MakeShared(MainGfxPipeline);
  RegisterPipeline(main);
}

#include "GraphicsPipeline.h"
#include "core/EngineCore.h"
#include "core/d3dx12.h"
#include "core/macros.h"
#include "infra/command/CommandAllocator.h"
#include "infra/command/CommandList.h"
#include "infra/command/CommandQueue.h"
#include "infra/pipeline/PipelineState.h"
#include "infra/pipeline/RootSignature.h"
#include "infra/surface/RenderTargetViews.h"
#include "infra/surface/SynchronisationController.h"
#include "infra/window/GameWindow.h"

void GraphicsPipeline::Setup() {
  m_pso = MakeShared(PipelineState);
  m_cmdList = MakeShared(CommandList);
  m_rootSignature = MakeShared(RootSignature);
  Setup(m_pso);
  m_pso->Finalize();
  m_cmdList->Create(m_pso);
  SetupResources();
  m_cmdList->Close();
}

void GraphicsPipeline::Setup(std::shared_ptr<PipelineState> pso) {}

void GraphicsPipeline::SetupResources() {}

void GraphicsPipeline::Render() {

}

void GraphicsPipeline::RenderAll() {
   ThrowOnFail(
      m_cmdList->GetCommandList()->Reset(CommandAllocator::Get()->GetCommandAllocator().Get(),
                      m_pso->GetPSO().Get()));
  m_cmdList->GetCommandList()->SetGraphicsRootSignature(m_rootSignature->GetRootSignature().Get());
  auto viewport = GameWindow::Get()->GetViewport();
  auto srect = GameWindow::Get()->GetScissorRect();
  m_cmdList->GetCommandList()->RSSetViewports(1, &viewport);
  m_cmdList->GetCommandList()->RSSetScissorRects(1, &srect);

  auto resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(RenderTargetViews::Get()->GetRTV(SynchronisationController::Get()->GetFrameIndex()).Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
  m_cmdList->GetCommandList()->ResourceBarrier(1, &resourceBarrier);

  CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(RenderTargetViews::Get()->GetHeap()->GetCPUDescriptorHandleForHeapStart(), SynchronisationController::Get()->GetFrameIndex(), RenderTargetViews::Get()->GetDescriptorSize());

  m_cmdList->GetCommandList()->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
  const float clearColor[] = {0.0f, 1.f, 0.4f, 1.0f};
  m_cmdList->GetCommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

  m_cmdList->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  
  this->Render();

  resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(RenderTargetViews::Get()->GetRTV(SynchronisationController::Get()->GetFrameIndex()).Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
  m_cmdList->GetCommandList()->ResourceBarrier(1, &resourceBarrier);
  m_cmdList->GetCommandList()->Close();
  ID3D12CommandList* ppCommandLists[] = {m_cmdList->GetCommandList().Get() };
  CommandQueue::Get()->GetCommandQueue()->ExecuteCommandLists(1, ppCommandLists);
}

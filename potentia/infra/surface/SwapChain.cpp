#include "SwapChain.h"

#include "SynchronisationController.h"
#include "infra/window/GameWindow.h"
#include "infra/command/CommandQueue.h"

void SwapChain::Create() {
  ComP(IDXGIFactory4) factory;
  ThrowOnFail(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory)));

  DXGI_SWAP_CHAIN_DESC1 desc = {};
  desc.BufferCount = SynchronisationController::Get()->GetFrameCount();
  auto windowSize = GameWindow::Get()->GetWindowSize();
  desc.Width = windowSize.x;
  desc.Height = windowSize.y;
  desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  desc.SampleDesc.Count = 1;

  ComP(IDXGISwapChain1) swapChain;
  ThrowOnFail(factory->CreateSwapChainForHwnd(
      CommandQueue::Get()->GetCommandQueue().Get(),
      GameWindow::Get()->GetRawHandle(), &desc, nullptr, nullptr,
      &swapChain));

  ThrowOnFail(factory->MakeWindowAssociation(
      GameWindow::Get()->GetRawHandle(), DXGI_MWA_NO_ALT_ENTER));
  
  ThrowOnFail(swapChain.As(&m_swapChain));

  SynchronisationController::Get()->SetFrameIndex(m_swapChain->GetCurrentBackBufferIndex());
}

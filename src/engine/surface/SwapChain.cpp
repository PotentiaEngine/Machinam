#include "SwapChain.h"

#include <dxgi.h>
#include <winuser.h>

#include "engine/command/CommandQueue.h"
#include "engine/surface/SynchronisationController.h"
#include "engine/window/AppWindow.h"
#include "utils.h"

void SwapChain::Create() {
  cptr(dxgi(Factory4)) factory;
  ThrowOnFail(CreateDXGIFactory2(0, IID_PPV_ARGS(&factory)));

  DXGI_SWAP_CHAIN_DESC1 desc = {};
  desc.BufferCount = SynchronisationController::Instance()->GetFrameCount();
  auto windowSize = AppWindow::Instance()->GetWindowSize();
  desc.Width = windowSize.x;
  desc.Height = windowSize.y;
  desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  desc.SampleDesc.Count = 1;

  cptr(dxgi(SwapChain1)) swapChain;
  ThrowOnFail(factory->CreateSwapChainForHwnd(
      CommandQueue::Instance()->GetCommandQueue().Get(),
      AppWindow::Instance()->GetRawHandle(), &desc, nullptr, nullptr,
      &swapChain));

  ThrowOnFail(factory->MakeWindowAssociation(
      AppWindow::Instance()->GetRawHandle(), DXGI_MWA_NO_ALT_ENTER));
  
  ThrowOnFail(swapChain.As(&m_swapChain));

  SynchronisationController::Instance()->SetFrameIndex(m_swapChain->GetCurrentBackBufferIndex());

}

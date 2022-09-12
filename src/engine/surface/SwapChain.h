#pragma once

#include "engine/base/Singleton.h"
class SwapChain : public Singleton<SwapChain> {
public: 
  void Create();
  Getter(cptr(dxgi(SwapChain1)), SwapChain, m_swapChain);

 private:
  cptr(dxgi(SwapChain3)) m_swapChain;
};

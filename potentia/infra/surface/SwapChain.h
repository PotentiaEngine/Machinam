#pragma once

#include "core/EngineCore.h"
#include "core/base/Singleton.h"

class SwapChain : public Singleton<SwapChain> {
public: 
  void Create();
  Getter(ComP(IDXGISwapChain3), SwapChain, m_swapChain);

 private:
  ComP(IDXGISwapChain3) m_swapChain;
};

#pragma once

#include "engine/base/Singleton.h"

class CommandAllocator : public Singleton<CommandAllocator> {
 public:
  void Create();
  Getter(cptr(d3d(CommandAllocator)), CommandAllocator, m_commandAllocator);

 private:
  cptr(d3d(CommandAllocator)) m_commandAllocator;
};

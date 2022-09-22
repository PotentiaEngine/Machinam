#pragma once

#include <potentia-core/pch.h>

class window {
  public:
    virtual void initialize() = 0;
    virtual void destroy() = 0;
};

#pragma once

#include <potentia-core/pch.h>

class pipeline_layout {
  public:
    virtual void initialize() = 0;
    virtual void destroy() = 0;
    virtual void finalize() = 0;
};


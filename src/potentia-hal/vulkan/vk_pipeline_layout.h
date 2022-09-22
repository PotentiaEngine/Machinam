#pragma once

#include "potentia-hal/interface/pipeline_layout.h"

class vk_pipeline_layout : public pipeline_layout {
  public:
    void initialize() override;
    void destroy() override;
    void finalize() override;
};

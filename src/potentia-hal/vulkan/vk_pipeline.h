#pragma once

#include "potentia-hal/interface/pipeline.h"

class vk_pipeline : public pipeline {
public:
  void initialize(std::shared_ptr<pipeline_layout> layout) override;
  void destroy() override;
  std::shared_ptr<commander> get_commander() override;
};

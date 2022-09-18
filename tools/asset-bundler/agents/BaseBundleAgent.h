#pragma once

#include "common.h"
#include <string>

class BaseBundleAgent {
  virtual bool IsFileType(std::string file) = 0;
  virtual BundleRecord Process(std::string file) = 0;
};

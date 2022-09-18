#pragma once

#include <memory>
#include <string>
#include <vector>
#include "agents/BaseBundleAgent.h"
#include "common.h"

class AssetBundler {
  public:
    void setup();
    void Run();
    void Output();
    void SetDirectory(std::string dir) { m_directory = dir; };

  protected:
    std::string m_directory;
    bool m_isDryRun;
    bool m_isCompressed;
    PreBundle m_bundles;
    std::vector<std::shared_ptr<BaseBundleAgent>> m_agents;
};

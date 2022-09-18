#include <CLI/App.hpp>
#include <CLI/CLI.hpp>

int main(int argc, char** argv) {
  CLI::App app{"Asset Bundling utility for the Potentia Game Engine"};

  std::string directory = "assets";
  app.add_option("-d,--directory", directory, "Path to directory containing assets to bundle");

  CLI11_PARSE(app, argc, argv);
  return 0;
}

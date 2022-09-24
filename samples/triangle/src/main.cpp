#include "potentia-engine/engine_runtime.h"
int main() {
  auto runtime = engine_runtime::create_instance();
  runtime->run();
}

#ifndef UNICODE
#define UNICODE
#endif

#include "pch.h"
#include "engine/EngineRuntime.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine,
                   INT nCmdShow) {

  auto runtime = mk_sptr(EngineRuntime);
  return runtime->run(hInstance, nCmdShow);
 }

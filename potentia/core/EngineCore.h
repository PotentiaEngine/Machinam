#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <shellapi.h>
#include <wincodec.h>
#include <windows.h>
#include <windowsx.h>
#include <wrl.h>

#include <memory>
#include <string>
#include <vector>
#include <comdef.h>
#include "d3dx12.h"
#include "macros.h"
using namespace DirectX;

#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "d3d12")
#pragma comment(lib, "dxgi")

inline void ThrowOnFail(HRESULT hr) {
 
if (FAILED(hr)) {
  _com_error err(hr);
  throw std::exception("IT BROK???");
 }
}

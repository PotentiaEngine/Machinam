#pragma once

#include <exception>
#include <windows.h>

inline void ThrowOnFail(HRESULT hr) {
 if (FAILED(hr)) {
   throw std::exception("IT BROK???");
 }
}


#define Str std::string
#define WStr std::wstring
#define mk_sptr(t, ...) ::std::make_shared<t>(__VA_ARGS__)
#define sptr(t) ::std::shared_ptr<t>

#define cptr(t) Microsoft::WRL::ComPtr<t>
#define d3d(t) ID3D12##t
#define dxgi(t) IDXGI##t

#define GetterCom(t, name, field) \
  t* Get##name() const { return field.Get(); }
#define Getter(t, name, field) \
  t Get##name() const { return field; }
#define ImplGetter(t, name) t Get##name();

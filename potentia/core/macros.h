#pragma once
#include <memory>

#define Shared(t) std::shared_ptr<t>
#define MakeShared(t, ...) std::make_shared<t>(__VA_ARGS__);

#define ComP(t) Microsoft::WRL::ComPtr<t>

#define GetterCom(t, name, field) \
  t* Get##name() const { return field.Get(); }
#define Getter(t, name, field) \
  t Get##name() const { return field; }
#define ImplGetter(t, name) t Get##name();

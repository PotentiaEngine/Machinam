#pragma once
#include "core/EngineCore.h"

template<class T>
class Singleton {
public:
  static Shared(T) Get();
protected:
  static Shared(T) instance;
};

template<class T>
Shared(T) Singleton<T>::Get() {
  if (instance == nullptr) {
    instance = MakeShared(T);
  }
  return instance; 
}

template<class T>
Shared(T) Singleton<T>::instance = nullptr; 

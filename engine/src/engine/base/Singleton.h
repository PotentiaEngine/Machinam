#pragma once

#include "pch.h"

template<class T>
class Singleton {
public:
  static sptr(T) Instance() {
    if (s_instance == nullptr) {
      s_instance = mk_sptr(T);
    }
    return s_instance;
  };
protected:
  static sptr(T) s_instance;
};

template<class T>
sptr(T) Singleton<T>::s_instance = nullptr;

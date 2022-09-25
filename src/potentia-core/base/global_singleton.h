#pragma once

#include <memory>
#include <potentia-core/pch.h>

template <class T> class global_singleton {
public:
  static std::shared_ptr<T> instance();

protected:
  static std::shared_ptr<T> m_instance;
};

template <class T> std::shared_ptr<T> instance() {
  if (global_singleton<T>::m_instance == nullptr) {
    global_singleton<T>::m_instance = std::make_shared<T>();
  }
  return global_singleton<T>::m_instance;
}

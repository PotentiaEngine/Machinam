#pragma once

#include "core/EngineCore.h"
#include "core/macros.h"
#include <functional>
#include <vector>


template<class T>
class Registry {
  public:
    void RunForAll(std::function<void(Shared(T))> fn);
    void Register(Shared(T) entry);
  private:
    Shared(std::vector<Shared(T)>) entries;
};

template<class T>
void Registry<T>::Register(std::shared_ptr<T> entry) {
  if (entries == nullptr) {
    entries = MakeShared(std::vector<Shared(T)>);
  }
  entries->push_back(entry);
}

template<class T>
void Registry<T>::RunForAll(std::function<void (std::shared_ptr<T>)> fn) {
  for (auto b : *entries) {
    fn(b);
  }
}

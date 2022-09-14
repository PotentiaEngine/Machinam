#pragma once

#include "core/EngineCore.h"
#include <functional>


template<class T>
class Registry {
  public:
    void RunForAll(std::function<void(Shared(T))> fn);
    void Register(Shared(T) entry);
  private:
    std::vector<Shared(T)> entries;
};

template<class T>
void Registry<T>::Register(std::shared_ptr<T> entry) {
  entries.push_back(entry);
}

template<class T>
void Registry<T>::RunForAll(std::function<void (std::shared_ptr<T>)> fn) {
  for (auto b : entries) {
    fn(b);
  }
}

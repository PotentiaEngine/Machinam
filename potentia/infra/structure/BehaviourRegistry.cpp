#include "BehaviourRegistry.h"

template<class T>
void BehaviourRegistry<T>::Register(std::shared_ptr<T> behaviour) {
  behaviours.push_back(behaviour);
}

template<class T>
void BehaviourRegistry<T>::RunForAll(std::function<void (std::shared_ptr<T>)> fn) {
  for (auto b : behaviours) {
    fn(b);
  }
}

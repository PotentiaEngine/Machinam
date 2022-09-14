#include "EngineBehaviour.h"

void EngineBehaviour::Update() {
  if (m_msg.has_value()) {
    ProcessTick(m_msg.value());
  }
  m_msg.reset();
}

void EngineBehaviour::SetMessage(MSG msg) {
  m_msg.emplace(msg);
}

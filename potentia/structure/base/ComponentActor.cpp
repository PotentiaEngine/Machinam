#include "ComponentActor.h"

void ComponentActor::AddBehaviour(Shared(Behaviour) behaviour) {
  m_behaviours->Register(behaviour);
}

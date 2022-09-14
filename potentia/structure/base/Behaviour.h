#include "core/EngineCore.h"

class Behaviour {
public:
  virtual void Created();
  virtual void Destroyed();
  virtual void Activated();
  virtual void Deactivated();
  virtual void Update();
  virtual void Render();
};

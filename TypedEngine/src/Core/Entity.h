#pragma once

#include "transform.h"
#include <string>

class Entity {
 public:
  Entity();
  virtual ~Entity();
  
  void setName(const std::string& name);
  inline void useScreenPosition(bool enabled) {
    screenPosition = enabled;
  }
  
  Transform transform;
  std::string name;

  bool screenPosition = false;

private:
  static int entityCount;
};

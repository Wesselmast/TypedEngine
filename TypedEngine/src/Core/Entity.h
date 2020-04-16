#pragma once

#include "transform.h"
#include <string>

class Entity {
 public:
  Entity();
  virtual ~Entity();
  
  void setName(const std::string& name);

  Transform transform;
  std::string name;

 private:
  static int entityCount;
};

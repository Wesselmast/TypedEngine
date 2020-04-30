#pragma once

#include "transform.h"
#include <string>

enum class Tag {
  PERMANENT,
  LEVEL,
  PLAY_MODE
};

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
  Tag tag = Tag::PERMANENT;
  
  bool screenPosition = false;

private:
  static int entityCount;
};

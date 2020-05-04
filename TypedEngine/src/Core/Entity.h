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

  Transform transform = { { 0.0f, 0.0f}, 0.0f, { 1.0f, 1.0f} };
  std::string name;
  Tag tag = Tag::PERMANENT;
  
  bool screenPosition = false;

private:
  static int entityCount;
};

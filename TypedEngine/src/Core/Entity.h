#pragma once

#include "Transform.h"
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

  void addScript(const char* fileName);   
  void removeScript(const char* fileName);   
  
  Transform transform = { { 0.0f, 0.0f}, 0.0f, { 1.0f, 1.0f} };
  std::string name;
  Tag tag = Tag::LEVEL;
  
  bool screenPosition = false;

private:
  static int entityCount;
};

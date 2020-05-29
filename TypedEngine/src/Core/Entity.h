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
  
  glm::vec2 offset;

  bool screenPosition = false;
  bool clickable = true;
  bool clicked = false;
  bool hidden = false;
  
  virtual bool checkForClick(glm::vec2 mousePos) { return false; }
  
  virtual int size() const {
    return sizeof(Entity);
  }
  virtual int typeID() const {
    return -1;
  };
  
private:
  static int entityCount;
};

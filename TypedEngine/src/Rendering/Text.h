#pragma once

#include "Core/Entity.h"
#include "glm/glm.hpp"
#include <string>

class Text : public Entity {
 public:
  Text();
  ~Text();
  Text(Transform transform);
  Text(const std::string& text);
  Text(Transform transform, const std::string& text);
public:
  glm::vec4 color;
  std::string text;
private:
  void init(Transform transform, const std::string& text);
};

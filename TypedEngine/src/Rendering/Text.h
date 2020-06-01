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
  Text(const std::string& text, const glm::vec4& color);
  Text(Transform transform, const std::string& text);
  Text(Transform transform, const std::string& text, const glm::vec4& color);

  virtual int typeID() const override { return 0; }; 
public:
  glm::vec4 color;
  std::string text;
};

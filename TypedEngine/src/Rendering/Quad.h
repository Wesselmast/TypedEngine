#pragma once

#include "Core/Entity.h"
#include "glm/glm.hpp"

class Quad : public Entity {
 public:
  Quad();
  ~Quad();
  Quad(Transform transform);
  Quad(const glm::vec4& color);
  Quad(Transform transform, const glm::vec4& color);

  virtual int typeID() const override { return 2; }; 

  virtual bool checkForClick(glm::vec2 mousePos) override;
public:
  glm::vec2 size = { 512.0f, 512.0f };
  glm::vec4 color;
};

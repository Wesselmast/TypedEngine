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

  virtual int size() const override {
    return sizeof(Quad);
  }  
  virtual int typeID() const override { return 2; }; 

public:
  glm::vec4 color;
private:
  void init();
};

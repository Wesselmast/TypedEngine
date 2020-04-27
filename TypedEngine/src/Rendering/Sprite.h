#pragma once

#include "core/entity.h"

class Texture;

class Sprite : public Entity {
 public:
  Sprite();
  ~Sprite();
  Sprite(Transform transform);
  Sprite(const char* texture);
  Sprite(Transform transform, const char* texture);
public:
  Texture* texture;
private:
  void init(Transform transform, const char* texture);
};

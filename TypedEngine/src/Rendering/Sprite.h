#pragma once

#include "Drawable.h"
#include "Texture.h"

class Sprite : public Drawable {
 public:
  Sprite();
  Sprite(Transform transform);
  Sprite(const char* texture);
  Sprite(Transform transform, const char* texture);
public:
  Texture* texture;
};
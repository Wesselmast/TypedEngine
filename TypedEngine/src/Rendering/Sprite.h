#pragma once

#include "Core/Entity.h"

class Texture;

class Sprite : public Entity {
 public:
  Sprite();
  ~Sprite();
  Sprite(Transform transform);
  Sprite(const char* texture);
  Sprite(Transform transform, const char* texture);
  void setTexture(const char* texture);
  
  virtual int size() const override {
    return sizeof(Sprite);
  }
  virtual int typeID() const override { return 1; }; 

public:
  Texture* texture;
private:
  void init(Transform transform, const char* texture);
};

#pragma once

#include "Core/Entity.h"
#include "Texture.h"

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
  const char* textureName;
private:
  void init();
};

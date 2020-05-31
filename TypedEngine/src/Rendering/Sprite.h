#pragma once

#include "Core/Entity.h"
#include "Texture.h"
#include <cstring>

class Sprite : public Entity {
 public:
  Sprite();
  ~Sprite();
  Sprite(Transform transform);
  Sprite(const char* texture);
  Sprite(Transform transform, const char* texture);
  bool setTexture(const char* texture);
  
  virtual int typeID() const override { return 1; }; 

  virtual bool checkForClick(glm::vec2 mousePos) override;
public:
  Texture* texture;
  char* textureName;
private:
  void init();
};

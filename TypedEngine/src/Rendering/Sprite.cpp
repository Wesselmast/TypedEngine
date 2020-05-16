#include "Sprite.h"

#include "RenderCommand.h"
#include "RenderAPI.h"
#include "Texture.h"

const char* defaultPath = "res/textures/T_Default.jpg";
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} }; 

Sprite::Sprite() {
  init(defaultTransform, defaultPath);
}

Sprite::Sprite(Transform transform) {
  init(transform, defaultPath);
}

Sprite::Sprite(const char* texture) {
  init(defaultTransform, texture);
}

Sprite::Sprite(Transform transform, const char* texture) {
  init(transform, texture);
}

void Sprite::init(Transform transform, const char* texture) {
  this->transform = transform;
  setTexture(texture);
  
  setName("Sprite");
  RenderCommand::addSprite(this);  
}

void Sprite::setTexture(const char* texture) {
  this->texture = RenderAPI::createTexture(texture);
}

Sprite::~Sprite() {
  printf("Deleted sprite: %s\n", name.c_str());
  RenderCommand::removeSprite(this);
}

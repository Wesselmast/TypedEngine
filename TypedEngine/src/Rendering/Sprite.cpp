#include "Sprite.h"

#include "RenderCommand.h"
#include "RenderAPI.h"

const char* defaultPath = "res/textures/T_Default.jpg";
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} }; 

Sprite::Sprite() {
  this->transform = defaultTransform;
  this->textureName = defaultPath;
  init();
}

Sprite::Sprite(Transform transform) {
  this->transform = transform;
  this->textureName = defaultPath;
  init();
}

Sprite::Sprite(const char* texture) {
  this->transform = defaultTransform;
  this->textureName = texture;
  init();
}

Sprite::Sprite(Transform transform, const char* texture) {
  this->transform = transform;
  this->textureName = texture;
  init();
}

void Sprite::init() {
  setTexture(textureName);
  
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

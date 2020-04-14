#include "sprite.h"


//this is very ugly, fix this @CleanUp
#include "RenderCommand.h"
#include "OpenGL/OpenGLTexture.h"

const char* defaultPath = "res/textures/T_Default.jpg";

Sprite::Sprite() {
  this->transform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} };
  this->texture = new OpenGLTexture(defaultPath);
  RenderCommand::addSprite(this);
}

Sprite::Sprite(Transform transform) {
  this->transform = transform;
  this->texture = new OpenGLTexture(defaultPath);
  RenderCommand::addSprite(this);
}

Sprite::Sprite(const char* texture) {
  this->transform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} };
  this->texture = new OpenGLTexture(texture);
  RenderCommand::addSprite(this);
}

Sprite::Sprite(Transform transform, const char* texture) {
  this->transform = transform;
  this->texture = new OpenGLTexture(texture);
  RenderCommand::addSprite(this);
}

Sprite::~Sprite() {
  RenderCommand::removeSprite(this);
}

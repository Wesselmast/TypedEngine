#include "sprite.h"


//this is very ugly, fix this @CleanUp
#include "RenderCommand.h"
#include "OpenGL/OpenGLTexture.h"

Sprite::Sprite() {
	this->transform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} };
	RenderCommand::addSprite(this);
}

Sprite::Sprite(Transform transform) {
	this->transform = transform;
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

#include "Sprite.h"

#include "RenderCommand.h"
#include "RenderAPI.h"

const char* defaultPath = "res/textures/T_Default.jpg";
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} }; 

Sprite::Sprite() : Sprite(defaultTransform, defaultPath) {}
Sprite::Sprite(Transform transform) : Sprite(transform, defaultPath) {}
Sprite::Sprite(const char* texture) : Sprite(defaultTransform, texture) {}

Sprite::Sprite(Transform transform, const char* texture) {
  this->transform = transform;
  unsigned int size = strlen(texture) + 1;
  textureName = new char[size];
  memcpy(textureName, texture, size);
  
  setName("Sprite");
  
  if(setTexture(this->textureName)) {
    RenderCommand::addSprite(this);
    return;
  }
  delete this;
}

bool Sprite::setTexture(const char* texture) {
  this->textureName = (char*)texture;
  this->texture = RenderAPI::createTexture(textureName);
  return this->texture->valid;
}
  
bool Sprite::checkForClick(glm::vec2 mousePos) {
  if(clickable) {
    glm::vec2 p0 = transform.position;
    glm::vec2 p1 = transform.position + (glm::vec2(texture->getWidth(), texture->getHeight()) * transform.scale);
    
    if(mousePos.x > p0.x && mousePos.x < p1.x) {
      if(mousePos.y > p0.y && mousePos.y < p1.y) {
	clicked = true;
	offset = glm::vec2(p0.x - mousePos.x, p0.y - mousePos.y);
	return true;
      }
    }
  }
  return false;
}

Sprite::~Sprite() {
  printf("Deleted sprite: %s\n", name.c_str());
  RenderCommand::removeSprite(this);
}

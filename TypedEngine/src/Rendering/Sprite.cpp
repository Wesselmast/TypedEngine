#include "Sprite.h"

#include "RenderCommand.h"
#include "RenderAPI.h"

const char* defaultPath = "res/textures/T_Default.jpg";
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} }; 

Sprite::Sprite() {
  this->transform = defaultTransform;
  this->textureName = (char*)defaultPath;
  init();
}

Sprite::Sprite(Transform transform) {
  this->transform = transform;
  this->textureName = (char*)defaultPath;
  init();
}

Sprite::Sprite(const char* texture) {
  this->transform = defaultTransform;
  unsigned int size = strlen(texture) + 1;
  textureName = new char[size];
  memcpy(textureName, texture, size);
  init();
}

Sprite::Sprite(Transform transform, const char* texture) {
  this->transform = transform;
  unsigned int size = strlen(texture) + 1;
  textureName = new char[size];
  memcpy(textureName, texture, size);
  init();
}

void Sprite::init() {
  setName("Sprite");
  if(setTexture(textureName)) {
    RenderCommand::addSprite(this);  
    return;
  }
  delete this;
}

bool Sprite::setTexture(const char* texture) {
  this->textureName = (char*)texture;
  this->texture = RenderAPI::createTexture(texture);
  return this->texture->valid;
}
  
bool Sprite::checkForClick(glm::vec2 mousePos) {
  if(clickable) {
    glm::vec2 p0 = transform.position;
    glm::vec2 p1 = transform.position + glm::vec2(texture->getWidth(), texture->getHeight());
    
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

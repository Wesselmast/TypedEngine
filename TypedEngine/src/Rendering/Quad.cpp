#include "Quad.h"

#include "RenderCommand.h"
#include "RenderAPI.h"
#include <math.h>

const glm::vec4 defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f};
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} }; 

Quad::Quad() : Quad(defaultTransform, defaultColor) {}
Quad::Quad(Transform transform) : Quad(transform, defaultColor) {}
Quad::Quad(const glm::vec4& color) : Quad(defaultTransform, color) {}

Quad::Quad(Transform transform, const glm::vec4& color) {
  this->transform = transform;
  this->color = color;
  setName("Quad");
  RenderCommand::addQuad(this);  
}

bool Quad::checkForClick(glm::vec2 mousePos) {
  if(clickable) {
    glm::vec2 p0 = transform.position;
    glm::vec2 p1 = transform.position + size * transform.scale;
    
    if(mousePos.x > p0.x && mousePos.x < p1.x) {
      if(mousePos.y > p0.y && mousePos.y < p1.y) {
	offset = glm::vec2(p0.x - mousePos.x, p0.y - mousePos.y);
	return true;
      }
    }
  }
  return false;
}

Quad::~Quad() {
  printf("Deleted quad: %s\n", name.c_str());
  RenderCommand::removeQuad(this);
}

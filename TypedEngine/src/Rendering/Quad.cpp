#include "PCH.h"

#include "Quad.h"

#include "RenderCommand.h"
#include "RenderAPI.h"

const glm::vec4 defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f};
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} }; 

Quad::Quad() {
  init(defaultTransform, defaultColor);
}

Quad::Quad(Transform transform) {
  init(transform, defaultColor);
}

Quad::Quad(const glm::vec4& color) {
  init(defaultTransform, color);
}

Quad::Quad(Transform transform, const glm::vec4& color) {
  init(transform, color);
}

void Quad::init(Transform transform, const glm::vec4& color) {
  this->transform = transform;
  this->color = color;

  setName("Quad");
  RenderCommand::addQuad(this);  
}

Quad::~Quad() {
  printf("Deleted quad: %s\n", name.c_str());
  RenderCommand::removeQuad(this);
}

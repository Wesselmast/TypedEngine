#include "Text.h"

#include "RenderCommand.h"
#include "RenderAPI.h"

const std::string defaultText = "New Text";
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} };
const glm::vec4 defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f }; 

Text::Text() {
  this->transform = defaultTransform;
  this->color = defaultColor; 
  this->text = defaultText;
  init();
}

Text::Text(Transform transform) {
  this->transform = transform;
  this->color = defaultColor; 
  this->text = defaultText;
  init();
}

Text::Text(const std::string& text) {
  this->transform = defaultTransform;
  this->color = defaultColor; 
  this->text = text;
  init();
}

Text::Text(Transform transform, const std::string& text) {
  this->transform = transform;
  this->color = defaultColor; 
  this->text = text;
  init();
}

void Text::init() {  
  setName("Text");
  RenderCommand::addText(this);  
}

Text::~Text() {
  printf("Deleted text: %s\n", name.c_str());
  RenderCommand::removeText(this);
}

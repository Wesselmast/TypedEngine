#include "PCH.h"

#include "Text.h"



#include "RenderCommand.h"
#include "RenderAPI.h"

const std::string defaultText = "New Text";
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} };
const glm::vec4 defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f }; 

Text::Text() {
  init(defaultTransform, defaultText);
}

Text::Text(Transform transform) {
  init(transform, defaultText);
}

Text::Text(const std::string& text) {
  init(defaultTransform, text);
}

Text::Text(Transform transform, const std::string& text) {
  init(transform, text);
}

void Text::init(Transform transform, const std::string& text) {
  this->transform = transform;
  this->text = text;
  this->color = defaultColor; 
  
  setName("Text");
  RenderCommand::addText(this);  
}

Text::~Text() {
  printf("Deleted text: %s\n", name.c_str());
  RenderCommand::removeText(this);
}

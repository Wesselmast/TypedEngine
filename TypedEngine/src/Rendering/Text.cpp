#include "Text.h"

#include "RenderCommand.h"
#include "RenderAPI.h"

const std::string defaultText = "New Text";
const Transform defaultTransform = { {0.0f, 0.0f}, 0.0f, {1.0f, 1.0f} };
const glm::vec4 defaultColor = { 1.0f, 1.0f, 1.0f, 1.0f }; 

Text::Text() : Text(defaultTransform, defaultText, defaultColor) {}
Text::Text(Transform transform) : Text(transform, defaultText, defaultColor) {}
Text::Text(const std::string& text) : Text(defaultTransform, text, defaultColor) {}
Text::Text(const std::string& text, const glm::vec4& color) : Text(defaultTransform, text, color) {}
Text::Text(Transform transform, const std::string& text) : Text(transform, text, defaultColor) {}

Text::Text(Transform transform, const std::string& text, const glm::vec4& color) {
  this->transform = transform;
  this->color = color; 
  this->text = text;
  setName("Text");
  RenderCommand::addText(this);  
}

Text::~Text() {
  printf("Deleted text: %s\n", name.c_str());
  RenderCommand::removeText(this);
}

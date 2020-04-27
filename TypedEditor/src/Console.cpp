#include "Console.h"

#include "Rendering/text.h"
#include "Rendering/quad.h"
#include "input/input.h"

#include "window/window.h"
#include <string>

glm::vec2 startSize;

Console::Console(Window* window) : window(window) {
  text = new Text(); //@CleanUp: I REALLY WANT TEXT COLOR
  text->useScreenPosition(true);
  text->transform.scale = { 0.75f, 0.75f };
  text->color = {220 / 255.0f, 220 / 255.0f, 204 / 255.0f, 1.0f};
  panel = new Quad({ 63/255.0f, 63/255.0f, 63/255.0f, 1.0f });
  panel->useScreenPosition(true);
  startSize = window->getSize();
}

void Console::refresh() {
  if (!this) return;
  float w = window->getSize().x;
  float h = window->getSize().y;
  float wS = w / startSize.x;
  float hS = h / startSize.y;
  
  panel->transform.position = { -w, -h/2 };
  panel->transform.scale = { 3.0f * wS, -0.5f * hS };
  text->transform.position = { -w/2 - (40.0f * wS), -h/4 - (40.0f * hS)} ;
}

void Console::recieveKey(Key key, Modifier mod) {
  if(key == Key::ENTER) {
    text->text.clear();
    return;
  }
  if(key == Key::BACKSPACE) {
    if(text->text != "") {
      text->text.pop_back();
    }
    return;
  }
  text->text.push_back((char)Input::convertKey(key, mod));
}

Console::~Console() {
  delete panel;
}

#include "Console.h"

#include "Rendering/text.h"
#include "Rendering/quad.h"

#include "window/window.h"

Console::Console(Window* window) : window(window) {
  panel = new Quad({0.0f, 0.0f, 0.0f, 1.0f});
  panel->useScreenPosition(true);
}

void Console::refresh() {
  float w = window->getSize().x;
  float h = window->getSize().y;

  panel->transform.position = { -w, -h/2 };
  panel->transform.scale = { 3.0f, -0.5f };
}

Console::~Console() {
  delete panel;
}

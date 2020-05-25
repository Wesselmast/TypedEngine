#include "App.h"

#include "Core/Transform.h"
#include "Rendering/Sprite.h"
#include "Rendering/Text.h"
#include "Rendering/Quad.h"
#include "Console.h"

#include <stdio.h>

bool consoleEnabled = false;
glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

glm::vec2 position = glm::vec3(0, 0, 0);
const float zoomSpeed = 0.5f;
const float panSpeed = 750.0f;

Text* fpsCounter = new Text();
Console* console;

void App::begin() {
  Sprite test;
  console = new Console(window);
  
  Sprite* sprite  = new Sprite("res/textures/T_Wood.jpg");
  sprite->transform.scale *= -5.0f;

  fpsCounter->useScreenPosition(true);
  fpsCounter->tag = Tag::PERMANENT;

  Sprite* AC = new Sprite({{-4800.0f, 500.0f}, 0.0f, {1.0f, 1.0f}}, "res/textures/4kAC.jpg");
  AC->addScript("tree.lua");
  AC->addScript("main.lua");
}

void App::tick(float deltaTime, float time) {
  position += input * deltaTime * zoom * panSpeed;
  camera->setPosition(position);
  camera->setScale(glm::vec2(zoom));

  fpsCounter->color = { 0.0f, 0.0f, 0.0f, 1.0f };
  fpsCounter->text = "FPS: " + std::to_string((int)(1/deltaTime));
}

void App::onKeyPressed(Key key, Modifier mod) {
  if(key == Key::ESCAPE) {
    window->close(); 
    return;
  } 
  
  if(key == Key::GRAVE) {
    consoleEnabled = !consoleEnabled;
    return;
  }

  if(consoleEnabled) {
    console->recieveKey(key, mod);
    return;
  }
  
  switch (key) {
  case Key::W: input.y =  1.0f; break;
  case Key::A: input.x = -1.0f; break;
  case Key::S: input.y = -1.0f; break;
  case Key::D: input.x =  1.0f; break;
  case Key::F: position = {0.0f, 0.0f}; break;
  }
}

void App::onKeyReleased(Key key, Modifier mod) {
  switch (key) {
  case Key::W: input.y =  0.0f; break;
  case Key::A: input.x =  0.0f; break;
  case Key::S: input.y =  0.0f; break;
  case Key::D: input.x =  0.0f; break;
  }
}

void App::onMouseScrolled(float offsetX, float offsetY) {
  zoom += -offsetY * zoomSpeed;
  if (zoom <= 0.01f) {
    zoom = 0.1f;
  }
  else if (zoom >= 10) {
    zoom = 10;
  }
}

void App::onWindowRefreshed() {
  float w = window->getSize().x;
  float h = window->getSize().y;
  fpsCounter->transform.position = { -w/2 + 30.0f, h/2 - 30.0f };
  console->refresh();
  camera->updateProjection();
}

void App::onMousePressed(MouseButton button) {
  float x = window->getMousePosition().x;
  float y = window->getMousePosition().y;
  printf("Mouse Position: %f, %f\n", x, y);
}

Application* createApplication() {
  return new App();
}

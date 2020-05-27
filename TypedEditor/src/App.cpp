#include "App.h"

#include "Core/Transform.h"
#include "Core/Math.h"

#include "Rendering/Sprite.h"
#include "Rendering/Text.h"
#include "Rendering/Quad.h"
#include "Rendering/RenderCommand.h"

#include "Console.h"

#include <stdio.h>
#include <math.h>

bool consoleEnabled = false;
glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

glm::vec2 position = glm::vec3(0, 0, 0);
const float zoomSpeed = 0.5f;
const float panSpeed = 750.0f;

Text* fpsCounter = new Text();
Console* console;

Sprite* mouseTest;
Entity* clickedObject = nullptr;

void App::begin() {
  console = new Console(window);
  
  Sprite* sprite  = new Sprite("res/textures/T_Wood.jpg");
  sprite->transform.scale *= -5.0f;

  mouseTest = new Sprite("res/textures/T_Tree.png");
  
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

  if(clickedObject) {
    clickedObject->transform.position = screenToWorld(camera, window, window->getMousePosition()) + clickedObject->offset;
  }
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

void App::onMousePressed(MouseButton button, Modifier mod) {
  glm::vec2 mousePos = screenToWorld(camera, window, window->getMousePosition());

  std::vector<Entity*> entities;
  RenderCommand::getTagged(Tag::LEVEL, &entities);
  for(auto e : entities) {
    if(e->checkForClick(mousePos)) {
      clickedObject = e;
      break;
    }
  }
}

void App::onMouseReleased(MouseButton button, Modifier mod) {
  std::vector<Entity*> entities;
  RenderCommand::getTagged(Tag::LEVEL, &entities);
  for(auto e : entities) {
    e->clicked = false;
  }
  clickedObject = nullptr;
}

Application* createApplication() {
  return new App();
}

#include "App.h"

#include "Core/Transform.h"
#include "Rendering/Sprite.h"
#include "Rendering/Text.h"
#include "Rendering/Quad.h"

#include "luamanager.h"

#include <iostream>
#include <string>

glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

glm::vec2 position = glm::vec3(0, 0, 0);
const float zoomSpeed = 0.5f;
const float panSpeed = 750.0f;

void App::begin() {
  treeSprite = new Sprite("res/textures/T_Tree.png"); 
  treeSprite->transform.position = { 1000, 1250 };
  
  new Text("BEANS ARE BETTER!");
  new Quad({0.5f, 0.5f, 1.0f, 0.5f});
  
  for (int i = 1; i < 50; i++) {
    new Sprite({{ 512.0f * i, 0.0f }, 0.0f, { 1.0f, 1.0f}});
  }
  luaFuture = std::async(std::launch::async, &LuaManager::compileLua);
}

void App::tick(float deltaTime, float time) {
  position += input * deltaTime * zoom * panSpeed;
  camera->setPosition(position);
  camera->setScale(glm::vec2(zoom));

  const float rotationSpeed = 5.0f;

  // @CleanUp: There should be an option for culling to get turned off per object. So the tree can actually be inversed properly.
  treeSprite->transform.scale.x = (glm::sin(time * rotationSpeed) + 1.0f) / 2;
}

void App::onKeyPressed(Key key, Modifier mod) {
  switch (key) {
  case Key::W: input.y =  1.0f; break;
  case Key::A: input.x = -1.0f; break;
  case Key::S: input.y = -1.0f; break;
  case Key::D: input.x =  1.0f; break;
  case Key::C: luaFuture = std::async(std::launch::async, &LuaManager::compileLua); break;
  case Key::F: position = {0.0f, 0.0f}; break;
  case Key::ESCAPE: window->close(); break;
  }
}

void App::onKeyReleased(Key key, Modifier mod) {
  switch (key) {
  case Key::W: input.y =  0.0f; break;
  case Key::A: input.x = -0.0f; break;
  case Key::S: input.y = -0.0f; break;
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

Application* createApplication() {
  return new App();
}

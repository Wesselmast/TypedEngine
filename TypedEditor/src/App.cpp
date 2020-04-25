#include "App.h"

#include "Core/Transform.h"
#include "Rendering/Sprite.h"
#include "Rendering/Text.h"
#include "Rendering/Quad.h"
#include "Console.h"

#include "luamanager.h"

#include <iostream>
#include <string>

glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

glm::vec2 position = glm::vec3(0, 0, 0);
const float zoomSpeed = 0.5f;
const float panSpeed = 750.0f;

Text* t =  new Text("");
Text* fpsCounter = new Text();
Console* console;

void App::begin() {
  console = new Console(window);
  treeSprite = new Sprite("res/textures/T_Tree.png"); 
  treeSprite->transform.position = { 1000, 1250 };
  
  Sprite* sprite  = new Sprite("res/textures/T_Wood.jpg");
  sprite->transform.scale *= -5.0f;

  fpsCounter->useScreenPosition(true);
  
  for (int i = 0; i < 50; i++) {
    // @CleanUp: Transforms are still weird right now. Positions have to follow scale
    new Quad({{ (512.0f + 250.0f) * i, 0.0f }, 0.0f, { 1.0f, 1.0f}}, {1 - i/50.0f, 1 - i/50.0f, 1 - i/50.0f, 1.0f});
    new Text({{ ((512.0f + 250.0f)/4 * i), 128.0f / 3.0f }, 0.0f, { 3.0f, 3.0f}}, std::to_string(i + 1));   //@CleanUp: Add setting color of the text
  }
  luaFuture = std::async(std::launch::async, &LuaManager::compileLua);
}

void App::tick(float deltaTime, float time) {
  position += input * deltaTime * zoom * panSpeed;
  camera->setPosition(position);
  camera->setScale(glm::vec2(zoom));

  const float rotationSpeed = 5.0f;
  treeSprite->transform.scale.x = (glm::sin(time * rotationSpeed));
  treeSprite->transform.position.x = -(glm::sin(time * rotationSpeed)) * 1080.0f / 2;

  fpsCounter->text = "FPS: " + std::to_string((int)(1/deltaTime));
}

bool consoleEnabled = false;
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
  case Key::C: luaFuture = std::async(std::launch::async, &LuaManager::compileLua); break;
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
}

Application* createApplication() {
  return new App();
}

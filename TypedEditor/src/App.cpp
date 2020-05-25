#include "App.h"

#include "Core/Transform.h"
#include "Rendering/Sprite.h"
#include "Rendering/Text.h"
#include "Rendering/Quad.h"
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
bool transformTheMouseTest = false;



glm::vec2 worldToScreen(Camera* camera, Window* window, glm::vec2 point) {
  glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(point, 0.0f));
  glm::mat4 mvp = camera->getViewProjection() * position;
  glm::vec3 screenPos(mvp[3]);

  screenPos.x += 1.0f;
  screenPos.x *= 0.5f * window->getSize().x;
  screenPos.y += 1.0f;
  screenPos.y *= 0.5f * window->getSize().y;

  return glm::vec2(screenPos.x, screenPos.y);
}


glm::vec2 screenToWorld(Camera* camera, Window* window, glm::vec2 point) {
  double x = 2.0 * (point.x / window->getSize().x) - 1.0;
  double y = 2.0 * (point.y / window->getSize().y) - 1.0;

  glm::vec4 screenPos = glm::vec4(x, -y, -1.0f, 1.0f);

  return glm::vec3(glm::inverse(camera->getViewProjection()) * screenPos);
}

void App::begin() {
  console = new Console(window);
  
  Sprite* sprite  = new Sprite("res/textures/T_Wood.jpg");
  sprite->transform.scale *= -5.0f;

  mouseTest = new Sprite();
  
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

  if(transformTheMouseTest) {
    mouseTest->transform.position = screenToWorld(camera, window, window->getMousePosition());
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

void App::onMousePressed(MouseButton button) {
  float x = window->getMousePosition().x;
  float y = window->getMousePosition().y;

  glm::vec2 screenPos0 = worldToScreen(camera, window, mouseTest->transform.position - glm::vec2(0, mouseTest->texture->getHeight()));    // @CleanUp: Really terrible world to screen position stuff
  glm::vec2 screenPos1 = worldToScreen(camera, window, mouseTest->transform.position + glm::vec2(mouseTest->texture->getWidth(), 0));
  
  if(x > screenPos0.x && x < screenPos1.x) {
    if(y > screenPos0.y && y < screenPos1.y) {
      transformTheMouseTest = true;
      printf("COLLIDE!!!!\n");
      return;
    }
  }
  transformTheMouseTest = false;
  printf("Mouse Position: %f, %f\n", x, y);
  printf("Object Screen Position 0: %f, %f\n", screenPos0.x, screenPos0.y);
  printf("Object Screen Position 1: %f, %f\n", screenPos1.x, screenPos1.y);
  printf("Camera Position: %f, %f\n", camera->getPosition().x, camera->getPosition().y);
}

Application* createApplication() {
  return new App();
}

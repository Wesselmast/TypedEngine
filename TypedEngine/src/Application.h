#pragma once

#include "Window/Window.h"
#include "Rendering/Camera.h"
#include "Input/Input.h"

#include "glm/glm.hpp"


class Application {
public:
  virtual void begin() {}
  virtual void tick(float deltaTime, float time) {}
  virtual void end() {}
  
  virtual void onWindowResized(int width, int height) {}
  virtual void onWindowMoved(int posX, int posY) {}
  virtual void onWindowRefreshed() {}
  
  virtual void onMousePressed(MouseButton button) {}
  virtual void onMouseReleased(MouseButton button) {}
  virtual void onMouseMoved(int posX, int posY) {}
  virtual void onMouseScrolled(float offsetX, float offsetY) {}
  
  virtual void onKeyPressed(Key key, Modifier mod) {}
  virtual void onKeyReleased(Key key, Modifier mod) {}
  
  Window* window;
  Camera* camera;
  
  static Application* application;
};

extern Application* createApplication();

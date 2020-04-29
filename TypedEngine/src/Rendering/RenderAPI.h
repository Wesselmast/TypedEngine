#pragma once

#include "glm/glm.hpp"

class Texture;
class Renderer;
class Window;

enum class API {
  NONE,
  OPENGL
};

class RenderAPI {
 public:
  static Texture* createTexture(const char* path);
  static Renderer* createRenderer();
  static Window* createWindow(glm::vec2 size, const char* name, bool fullscreen = false);
  
  static API renderAPI;
};

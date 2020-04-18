#pragma once

#include "texture.h"
#include "renderer.h"

enum class API {
  NONE,
  OPENGL
};

class RenderAPI {
 public:
  static Texture* createTexture(const char* path);
  static Renderer* createRenderer();
  
  static API renderAPI;
};

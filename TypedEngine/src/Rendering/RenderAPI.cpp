#include "renderapi.h"

#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLRenderer.h"

API RenderAPI::renderAPI = API::OPENGL;

Texture* RenderAPI::createTexture(const char* path) {
  switch(renderAPI) {
  case API::OPENGL: return new OpenGLTexture(path);
  default: printf("RenderAPI is not valid!"); return nullptr;
  }
}

Renderer* RenderAPI::createRenderer() {
  switch(renderAPI) {
  case API::OPENGL: return new OpenGLRenderer();
  default: printf("RenderAPI is not valid!"); return nullptr;
  }
}

#include "PCH.h"

#include "renderapi.h"

#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLRenderer.h"
#include "Window/OpenGL/OpenGLWindow.h"

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

Window* RenderAPI::createWindow(glm::vec2 size, const char* name, bool fullscreen) {
  switch(renderAPI) {
  case API::OPENGL: return new OpenGLWindow(size, name, fullscreen);
  default: printf("RenderAPI is not valid!"); return nullptr;
  }
}

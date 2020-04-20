#include "glfw/glfw3.h"

#include "Application.h"

#include "Window/OpenGL/OpenGLWindow.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Sprite.h"

#include "Core/Transform.h"

#include "glm/glm.hpp"

Application* app;

static void callback_keyPressed(Key key, Modifier mod) { app->onKeyPressed(key, mod); }
static void callback_keyReleased(Key key, Modifier mod) { app->onKeyReleased (key, mod); }
static void callback_mouseScrolled(float offsetx, float offsety) { app->onMouseScrolled(offsetx, offsety); }

static std::string getName() {
  std::string name = "TypedEngine : ";
#ifdef TE_DEBUG
  name += "Debug";
#else
  name += "Release";
#endif
  return name;
}
int main() {

  app = createApplication();
  
  Window* window = new OpenGLWindow({ 680, 480 }, getName().c_str(), false);
  
  window->callback_keyPressed(callback_keyPressed);
  window->callback_keyReleased(callback_keyReleased);
  window->callback_mouseScrolled(callback_mouseScrolled);
  
  Camera* camera = new Camera(window);
  RenderCommand::init(camera);

  app->window = window;
  app->camera = camera;
  
  app->begin();

  float previous = (float)glfwGetTime();    //YUCK! @CleanUp: Make custom deltaTime function, don't want glfw in the main file
  
  while (window->isRunning()) {
    float time = (float)glfwGetTime();
    float deltaTime = time - previous;
    
    app->tick(deltaTime, time);

    RenderCommand::clear(glm::vec4(233 / 255.0f, 233 / 255.0f, 245 / 255.0f, 1.0f));
    RenderCommand::run();
    window->swapBuffers();
    
    previous = time;
  }

  // @CleanUp: This doesn't work currently, I should properly clean up though
  //RenderCommand::end();
  
  delete app;
  return 0;
}

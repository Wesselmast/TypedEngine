#include "glfw/glfw3.h"

#include "Application.h"

#include "Window/OpenGL/OpenGLWindow.h"
#include "Rendering/RenderCommand.h"

#include "glm/glm.hpp"

Application* app;
Window* window;
Camera* camera;

static void callback_keyPressed(Key key, Modifier mod) { app->onKeyPressed(key, mod); }
static void callback_keyReleased(Key key, Modifier mod) { app->onKeyReleased (key, mod); }
static void callback_mouseScrolled(float offsetx, float offsety) { app->onMouseScrolled(offsetx, offsety); }
static void callback_windowRefreshed() {
  app->onWindowRefreshed();
  camera->updateProjection();
}

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
  window = new OpenGLWindow({ 680, 480 }, getName().c_str(), false);
   
  window->callback_keyPressed(callback_keyPressed);
  window->callback_keyReleased(callback_keyReleased);
  window->callback_mouseScrolled(callback_mouseScrolled);
  window->callback_windowRefreshed(callback_windowRefreshed);

  camera = new Camera(window);
  RenderCommand::init(camera);

  app = createApplication();
  app->window = window;
  app->camera = camera;
  
  app->begin();

  float previous = (float)glfwGetTime();    //YUCK! @CleanUp: Make custom deltaTime function, don't want glfw in the main file
  
  while (window->isRunning()) {
    float time = (float)glfwGetTime();
    float deltaTime = time - previous;
    
    app->tick(deltaTime, time);

    RenderCommand::clear(glm::vec4(133 / 255.0f, 133 / 255.0f, 245 / 255.0f, 1.0f));
    RenderCommand::run();
    window->swapBuffers();
    
    previous = time;
  }

  RenderCommand::end();

  delete app;
  return 0;
}

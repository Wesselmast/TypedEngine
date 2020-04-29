#include "glfw/glfw3.h"   //@CleanUp: Get rid of this

#include "Application.h"

#include "Window/OpenGL/OpenGLWindow.h"   //@CleanUp: Clean this up too
#include "Rendering/RenderCommand.h"

#include "glm/glm.hpp"

extern "C" {
  #include "Scripting/TElua.h"
}

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

  init_lua();

  app = createApplication();
  app->window = window;
  app->camera = camera;

  app->begin();

  float previous = (float)glfwGetTime();    //YUCK! @CleanUp: Make custom deltaTime function, don't want glfw in the main file
  
  while (window->isRunning()) {
    float time = (float)glfwGetTime();
    float deltaTime = time - previous;
    
    app->tick(deltaTime, time);

    RenderCommand::clear({ 0.9f, 0.9f, 0.9f, 1.0f });
    RenderCommand::run();
    window->swapBuffers();
    
    previous = time;
  }

  close_lua();
  RenderCommand::end();

  delete app;
  return 0;
}

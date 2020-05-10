#include "Application.h"

#include "Rendering/RenderAPI.h"
#include "Rendering/RenderCommand.h"
#include "Scripting/LuaCommand.h"

Application* app;
Window* window;
Camera* camera;

static void callback_keyPressed(Key key, Modifier mod) { app->onKeyPressed(key, mod); }
static void callback_keyReleased(Key key, Modifier mod) { app->onKeyReleased (key, mod); }
static void callback_mouseScrolled(float offsetx, float offsety) { app->onMouseScrolled(offsetx, offsety); }
static void callback_windowRefreshed() {  app->onWindowRefreshed(); }
static void callback_mousePressed(MouseButton button) {  app->onMousePressed(button); }
static void callback_mouseMoved(float xPos, float yPos) {  app->onMouseMoved(xPos, yPos); }

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
  window = RenderAPI::createWindow({ 680, 480 }, getName().c_str(), false);

  window->callback_keyPressed(callback_keyPressed);
  window->callback_keyReleased(callback_keyReleased);
  window->callback_mouseScrolled(callback_mouseScrolled);
  window->callback_windowRefreshed(callback_windowRefreshed);
  window->callback_mouseMoved(callback_mouseMoved);
  window->callback_mousePressed(callback_mousePressed);

  camera = new Camera(window);
  RenderCommand::init(camera);

  LuaCommand::init();

  app = createApplication();
  app->window = window;
  app->camera = camera;

  app->begin();

  float previous = window->getTime();
  
  while (window->isRunning()) {
    float time = window->getTime();
    float deltaTime = time - previous;

    LuaCommand::tick(deltaTime, time);
    app->tick(deltaTime, time);

    RenderCommand::clear({ 0.9f, 0.9f, 0.9f, 1.0f });
    RenderCommand::run();

    window->swapBuffers();
    
    previous = time;
  }

  LuaCommand::close();
  RenderCommand::end();

  delete app;
  return 0;
}

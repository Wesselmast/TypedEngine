#pragma once

#include "../Window.h"

struct GLFWwindow;

class OpenGLWindow : public Window {
public:
  OpenGLWindow(glm::vec2 size, const char* name, bool fullscreen = false);
  ~OpenGLWindow();
  
  virtual glm::vec2 getSize() const override;
  virtual void setVSync(bool enabled) override;
  virtual void refreshViewport() override;
  virtual bool isRunning() const override;
  virtual void swapBuffers() override;
  virtual void close() override;
  virtual float getTime() override;
  
  static void callback_mouseScrolled(GLFWwindow* window, double offsetx, double offsety);
  static void callback_keyAction(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void callback_windowRefreshed(GLFWwindow* window);
  
private:
  GLFWwindow* window;
};

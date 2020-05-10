#include "OpenGLWindow.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

fptr_TwoFloat Window::mouseScrolledFunction;
fptr_TwoFloat Window::mouseMovedFunction;
fptr_MouseAction Window::mousePressedFunction;
fptr_KeyAction Window::keyPressedFunction;
fptr_KeyAction Window::keyReleasedFunction;
fptr_NoParams Window::windowRefreshFunction;

glm::vec2 OpenGLWindow::mousePosition = {0.0f, 0.0f};

OpenGLWindow::OpenGLWindow(glm::vec2 size, const char * name, bool fullscreen) {
  if (!glfwInit()) {
    // ERROR MESSAGE
    return;
  }
  
  GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;
  
  window = glfwCreateWindow((int)size.x, (int)size.y, name, monitor, NULL);
  if (!window) {
    glfwTerminate();
    // ERROR MESSAGE
    return;
  }

  glfwMakeContextCurrent(window);
  
  glfwSetScrollCallback(window, callback_mouseScrolled);
  glfwSetKeyCallback(window, callback_keyAction);
  glfwSetWindowRefreshCallback(window, callback_windowRefreshed);
  glfwSetCursorPosCallback(window, callback_mouseMoved);
  glfwSetMouseButtonCallback(window, callback_mousePressed);
  
  setVSync(true);
}

OpenGLWindow::~OpenGLWindow() {
  glfwTerminate();
}

glm::vec2 OpenGLWindow::getSize() const {
  int width;
  int height;
  glfwGetFramebufferSize(window, &width, &height);

  return { (float)width, (float)height };
}

void OpenGLWindow::setVSync(bool enabled) {
  glfwSwapInterval(enabled);
}

void OpenGLWindow::refreshViewport() {
  glm::vec2 size = getSize();
  glViewport(0, 0, (GLsizei)size.x, (GLsizei)size.y);
}

bool OpenGLWindow::isRunning() const {
  glfwPollEvents();
  return !glfwWindowShouldClose(window);
}

void OpenGLWindow::swapBuffers() {
  glfwSwapBuffers(window);
}

void OpenGLWindow::close() {
  glfwSetWindowShouldClose(window, 1);
}

float OpenGLWindow::getTime() const {
  return (float)glfwGetTime();
}

glm::vec2 OpenGLWindow::getMousePosition() const {
  return mousePosition;
}

void OpenGLWindow::callback_mouseScrolled(GLFWwindow * window, double offsetx, double offsety) {
  mouseScrolledFunction((float)offsetx, (float)offsety);
}

void OpenGLWindow::callback_keyAction(GLFWwindow * window, int key, int scancode, int action, int mods) {
  switch (action) {
  case GLFW_PRESS:   keyPressedFunction(Input::convertKey(key), Input::convertMod(mods)); break;
  case GLFW_RELEASE: keyReleasedFunction(Input::convertKey(key), Input::convertMod(mods)); break;
  }
}

void OpenGLWindow::callback_windowRefreshed(GLFWwindow * window) {
  int width;
  int height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);
  windowRefreshFunction();
}

void OpenGLWindow::callback_mouseMoved(GLFWwindow* window, double xpos, double ypos) {
  mousePosition = {(float)xpos, (float)ypos};
  mouseMovedFunction((float)xpos, (float)ypos);
}

void OpenGLWindow::callback_mousePressed(GLFWwindow* window, int button, int action, int mods) {
  switch(action) {
  case GLFW_PRESS: mousePressedFunction(Input::convertMouseButton(button)); break;
  case GLFW_RELEASE: /*   MOUSE RELEASED EVENT   */ break;
  }
} 

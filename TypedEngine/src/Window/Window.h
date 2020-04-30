#pragma once

#include "Input/Input.h"
#include "glm/glm.hpp"

typedef void(*fptr_NoParams)();
typedef void(*fptr_TwoFloat)(float, float);
typedef void(*fptr_KeyAction)(Key, Modifier);
typedef void(*fptr_MouseAction)(MouseButton);

class Window {
public:
  virtual ~Window() = default;
  
  virtual void setVSync(bool enabled) = 0;
  virtual void refreshViewport() = 0;
  virtual bool isRunning() const = 0;
  virtual void swapBuffers() = 0;
  virtual glm::vec2 getSize() const = 0;
  virtual void close() = 0;
  virtual float getTime() const  = 0;
  virtual glm::vec2 getMousePosition() const = 0;
  
  void callback_mouseScrolled(fptr_TwoFloat function) { mouseScrolledFunction = function; }
  void callback_mouseMoved(fptr_TwoFloat function) { mouseMovedFunction = function; }
  void callback_mousePressed(fptr_MouseAction function) { mousePressedFunction = function; }
  void callback_keyPressed(fptr_KeyAction function) { keyPressedFunction = function; }
  void callback_keyReleased(fptr_KeyAction function) { keyReleasedFunction = function; }
  void callback_windowRefreshed(fptr_NoParams function) { windowRefreshFunction = function; }
  
protected:
  static fptr_TwoFloat mouseScrolledFunction; 
  static fptr_TwoFloat mouseMovedFunction;
  static fptr_MouseAction mousePressedFunction;
  static fptr_KeyAction keyPressedFunction;
  static fptr_KeyAction keyReleasedFunction;
  static fptr_NoParams windowRefreshFunction;
};

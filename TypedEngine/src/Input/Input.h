#pragma once

#include "InputManager.h"

class Input {
public:	
  static inline Key convertKey(int value) { return inputManager->convertValueToKey(value); }
  static inline Modifier convertMod(int value) { return inputManager->convertValueToModifier(value); }
  static inline MouseButton convertMouseButton(int value) { return inputManager->convertValueToMouseButton(value); }
  
  static inline int convertKey(Key key) { return inputManager->convertKeyToValue(key); }
  static inline int convertMod(Modifier mod) { return inputManager->convertModifierToValue(mod); }
  static inline int convertMouseButton(MouseButton button) { return inputManager->convertMouseButtonToValue(button); }
  
private:
  ~Input() {
    delete inputManager;
  }
  
  static InputManager* inputManager;
};

#pragma once

#include "../InputManager.h"

class OpenGLInputManager : public InputManager {
  virtual int convertKeyToValue(Key key, Modifier mod) override;
  virtual int convertModifierToValue(Modifier mod) override;
  virtual int convertMouseButtonToValue(MouseButton button) override;
  
  virtual Key convertValueToKey(int value) override;
  virtual Modifier convertValueToModifier(int value) override;
  virtual MouseButton convertValueToMouseButton(int value) override;
};

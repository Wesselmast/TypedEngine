#pragma once

enum class Key {
   NONE,
   A,
   B,
   C,
   D,
   E,
   F,
   G,
   H,
   I,
   J,
   K,
   L,
   M,
   N,
   O,
   P,
   Q,
   R,
   S,
   T,
   U,
   V,
   W,
   X,
   Y,
   Z,
   SPACE,
   APOSTROPHE,
   COMMA,
   MINUS,
   PERIOD,
   SLASH,
   ZERO,
   ONE,
   TWO,
   THREE,
   FOUR,
   FIVE,
   SIX,
   SEVEN,
   EIGHT,
   NINE,
   SEMICOLON,
   EQUAL,
   LEFT_BRACKET,
   RIGHT_BRACKET,
   BACKSLASH,
   GRAVE,
   ESCAPE,
   ENTER,
   TAB,
   BACKSPACE,
   INSERT,
   DELETE,
   RIGHT,
   LEFT,
   DOWN,
   UP,
   PAGE_UP,
   PAGE_DOWN,
   HOME,
   END,
   CAPS_LOCK,
   SCROLL_LOCK,
   SHIFT
};

enum class MouseButton {
   NONE,
   ONE,
   TWO,
   MIDDLE
};

enum class Modifier {
   NONE,
   SHIFT,
   CONTROL,
   ALT,
};

class InputManager { 
public:
  virtual int convertKeyToValue(Key key, Modifier mod) = 0;
  virtual int convertModifierToValue(Modifier mod) = 0;
  virtual int convertMouseButtonToValue(MouseButton button) = 0;
  
  virtual Key convertValueToKey(int value) = 0;
  virtual Modifier convertValueToModifier(int value) = 0;
  virtual MouseButton convertValueToMouseButton(int value) = 0;
};

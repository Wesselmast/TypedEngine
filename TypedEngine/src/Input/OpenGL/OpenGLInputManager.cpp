#include "OpenGLInputManager.h"

#include "GLFW/glfw3.h"

int OpenGLInputManager::convertKeyToValue(Key key) {
  switch (key) {
  case Key::SPACE:           return 32;
  case Key::APOSTROPHE:      return 39;
  case Key::COMMA:           return 44;
  case Key::MINUS:           return 45;
  case Key::PERIOD:          return 46;
  case Key::SLASH:           return 47;
  case Key::ZERO:            return 48;
  case Key::ONE:             return 49;
  case Key::TWO:             return 50;
  case Key::THREE:           return 51;
  case Key::FOUR:            return 52;
  case Key::FIVE:            return 53;
  case Key::SIX:             return 54;
  case Key::SEVEN:           return 55;
  case Key::EIGHT:           return 56;
  case Key::NINE:            return 57;
  case Key::SEMICOLON:       return 58;
  case Key::EQUAL:           return 59;
  case Key::A:               return 65;
  case Key::B:               return 66;
  case Key::C:               return 67;
  case Key::D:               return 68;					   ///////////////////////////////////////
  case Key::E:               return 69;					   //									//
  case Key::F:               return 70;					   //  MESSED UP, REPLACE WITH GL ONES  //
  case Key::G:               return 71;					   //									//
  case Key::H:               return 72;					   ///////////////////////////////////////
  case Key::I:               return 73;
  case Key::J:               return 74;
  case Key::K:               return 75;
  case Key::L:               return 76;
  case Key::M:               return 77;
  case Key::N:               return 78;
  case Key::O:               return 79;
  case Key::P:               return 80;
  case Key::Q:               return 81;
  case Key::R:               return 82;
  case Key::S:               return 83;
  case Key::T:               return 84;
  case Key::U:               return 85;
  case Key::V:               return 86;
  case Key::W:               return 87;
  case Key::X:               return 88;
  case Key::Y:               return 89;
  case Key::Z:               return 90;
  case Key::LEFT_BRACKET:    return 91;
  case Key::BACKSLASH:       return 92;
  case Key::RIGHT_BRACKET:   return 93;
  case Key::GRAVE:           return 96;
  case Key::ESCAPE:          return 256;
  case Key::ENTER:           return 257;
  case Key::TAB:             return 258;
  case Key::BACKSPACE:       return 259;
  case Key::INSERT:          return 260;
  case Key::DELETE:          return 261;
  case Key::RIGHT:           return 262;
  case Key::LEFT:            return 263;
  case Key::DOWN:            return 264;
  case Key::UP:              return 265;
  case Key::PAGE_UP:         return 266;
  case Key::PAGE_DOWN:       return 267;
  case Key::HOME:            return 268;
  case Key::END:             return 269;
  case Key::SHIFT:           return GLFW_KEY_LEFT_SHIFT;
  }
  return -1;
}

int OpenGLInputManager::convertModifierToValue(Modifier mod) {
  switch (mod) {
  case Modifier::SHIFT:      return GLFW_MOD_SHIFT;
  case Modifier::CONTROL:    return GLFW_MOD_CONTROL;
  case Modifier::ALT:        return GLFW_MOD_ALT;
  }
  return -1;
}

int OpenGLInputManager::convertMouseButtonToValue(MouseButton button) {
  switch (button) {
  case MouseButton::ONE:     return GLFW_MOUSE_BUTTON_1;
  case MouseButton::TWO:     return GLFW_MOUSE_BUTTON_2;
  case MouseButton::MIDDLE:  return GLFW_MOUSE_BUTTON_MIDDLE;
  }
  return -1;
}

Key OpenGLInputManager::convertValueToKey(int value) {
  switch (value) {
  case 32:                    return Key::SPACE;
		case 39:                    return Key::APOSTROPHE;
  case 44:                    return Key::COMMA;
  case 45:                    return Key::MINUS;
  case 46:                    return Key::PERIOD;
  case 47:                    return Key::SLASH;
  case 48:                    return Key::ZERO;
  case 49:                    return Key::ONE;
  case 50:                    return Key::TWO;
  case 51:                    return Key::THREE;
  case 52:                    return Key::FOUR;
  case 53:                    return Key::FIVE;
  case 54:                    return Key::SIX;
  case 55:                    return Key::SEVEN;
  case 56:                    return Key::EIGHT;
  case 57:                    return Key::NINE;
  case 58:                    return Key::SEMICOLON;
  case 59:                    return Key::EQUAL;
  case 65:                    return Key::A;
  case 66:                    return Key::B;
  case 67:                    return Key::C;
  case 68:                    return Key::D;
  case 69:                    return Key::E;
  case 70:                    return Key::F;
  case 71:                    return Key::G;
  case 72:                    return Key::H;
  case 73:                    return Key::I;
  case 74:                    return Key::J;
  case 75:                    return Key::K;
  case 76:                    return Key::L;
  case 77:                    return Key::M;
  case 78:                    return Key::N;
  case 79:                    return Key::O;
  case 80:                    return Key::P;
  case 81:                    return Key::Q;
  case 82:                    return Key::R;
  case 83:                    return Key::S;
  case 84:                    return Key::T;
  case 85:                    return Key::U;
  case 86:                    return Key::V;
  case 87:                    return Key::W;
  case 88:                    return Key::X;
  case 89:                    return Key::Y;
  case 90:                    return Key::Z;
  case 91:                    return Key::LEFT_BRACKET;
  case 92:                    return Key::BACKSLASH;
  case 93:                    return Key::RIGHT_BRACKET;
  case 96:                    return Key::GRAVE;
  case 256:                   return Key::ESCAPE;
  case 257:                   return Key::ENTER;
  case 258:                   return Key::TAB;
  case 259:                   return Key::BACKSPACE;
  case 260:                   return Key::INSERT;
  case 261:                   return Key::DELETE;
  case 262:                   return Key::RIGHT;
  case 263:                   return Key::LEFT;
  case 264:                   return Key::DOWN;
  case 265:                   return Key::UP;
  case 266:                   return Key::PAGE_UP;
  case 267:                   return Key::PAGE_DOWN;
  case 268:                   return Key::HOME;
  case 269:                   return Key::END;
  case GLFW_KEY_LEFT_SHIFT:   return Key::SHIFT;
  default:                    return Key::NONE;
  }
}

Modifier OpenGLInputManager::convertValueToModifier(int value) {
  switch (value) {
  case GLFW_MOD_SHIFT:        return Modifier::SHIFT;
  case GLFW_MOD_CONTROL:      return Modifier::CONTROL;
  case GLFW_MOD_ALT:          return Modifier::ALT;
  default:                    return Modifier::NONE;
  }
}

MouseButton OpenGLInputManager::convertValueToMouseButton(int value) {
  switch (value) {
  case GLFW_MOUSE_BUTTON_1:   return MouseButton::ONE;
  case GLFW_MOUSE_BUTTON_2:   return MouseButton::TWO;
  case GLFW_MOUSE_BUTTON_3:   return MouseButton::MIDDLE;
  default:                    return MouseButton::NONE;
  }
}

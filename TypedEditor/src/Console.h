#pragma once

#include <string>
#include <future>

class Text;
class Quad;
class Window;
enum class Key;
enum class Modifier;

class Console {
 public:
  void refresh();
  void recieveKey(Key key, Modifier mod);
  
  Console(Window* window);
  ~Console();
 private:
  Text* text;
  Quad* topBar;
  Text* topText;
  Quad* panel;
  Window* window;
};

#pragma once

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
  Quad* panel;
  Window* window;
};

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
  void setHidden(bool hidden);
  bool getHidden() const;

  static bool playMode;
  
  Console(Window* window);
  ~Console();
 private:
  Text* text;
  Quad* topBar;
  Text* topText;
  Quad* panel;
  Window* window;
  bool hidden = true;
};

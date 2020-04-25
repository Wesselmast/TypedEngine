#pragma once

class Quad;
class Window;

class Console {
 public:
  void refresh();

  Console(Window* window);
  ~Console();
 private:
  Quad* panel;
  Window* window;
};

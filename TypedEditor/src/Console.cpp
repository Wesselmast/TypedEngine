#include "Console.h"

#include "Rendering/text.h"
#include "Rendering/quad.h"
#include "input/input.h"

#include "window/window.h"
#include <string>

#include <stdio.h>

extern "C" {
  #include "Scripting/TElua.h"   //@CleanUp: I don't really want to include this in the editor (wrapper?!)
}

glm::vec2 startSize;

Console::Console(Window* window) : window(window) {
  text = new Text("");
  text->useScreenPosition(true);
  text->transform.scale = { 0.75f, 0.75f };
  text->color = {220 / 255.0f, 220 / 255.0f, 204 / 255.0f, 1.0f};

  topText = new Text("console");
  topText->useScreenPosition(true);
  topText->transform.scale = { 0.66f, 0.66f };
  topText->color = {240 / 255.0f, 223 / 255.0f, 175 / 255.0f, 1.0f};
  
  panel = new Quad({ 63/255.0f, 63/255.0f, 63/255.0f, 1.0f });
  panel->useScreenPosition(true);

  topBar = new Quad({ 48/255.0f, 48/255.0f, 48/255.0f, 1.0f });
  topBar->useScreenPosition(true);

  startSize = window->getSize();
}

void Console::refresh() {
  if (!this) return;
  float w = window->getSize().x;
  float h = window->getSize().y;
  float wS = w / startSize.x;
  float hS = h / startSize.y;
  
  panel->transform.position = { -w, -h/2 };
  panel->transform.scale = { 3.0f * wS, -0.5f * hS };
  topBar->transform.position = { -w, -h/2 };
  topBar->transform.scale = { 3.0f * wS, -0.08f * hS};
  text->transform.position = { -w/2 - (40.0f * wS), -h/4 - (60.0f * hS)} ;
  topText->transform.position = { -w/2 - (45.0f * wS), -h/4 - (40.0f * hS)} ;
}

void Console::recieveKey(Key key, Modifier mod) {
  if(key == Key::ENTER) {
    executeCommand(text->text);
    text->text.clear();
    return;
  }
  if(key == Key::BACKSPACE) {
    if(text->text != "") {
      text->text.pop_back();
    }
    return;
  }
  text->text.push_back((char)Input::convertKey(key, mod));
}

void Console::executeCommand(const std::string& command) {
  if(command == "run") {
    compile_lua();
    return;
  }
  if(command == "quit") {
    quit_lua();
    return;
  }
  printf("ERROR: Unknown command\n");
}

Console::~Console() {
  delete text;
  delete topBar;
  delete panel;
}

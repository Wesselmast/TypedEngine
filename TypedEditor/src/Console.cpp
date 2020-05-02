#include "Console.h"

#include "Rendering/text.h"
#include "Rendering/quad.h"
#include "input/input.h"

#include "window/window.h"
#include <string>

#include "Rendering/Rendercommand.h"

#include <stdio.h>

#include "ConsoleCommands.h"

extern "C" {
  #include "Scripting/TElua.h"   //@CleanUp: I don't really want to include this in the editor (wrapper?!)
}

void command_play(const std::string& command) {
  printf("\nENTERING PLAY MODE...\n\n"); 
  run_lua();
}

void command_stop(const std::string& command) {
  RenderCommand::removeTagged(Tag::PLAY_MODE);
  quit_lua();
  printf("\nENTERING EDITOR MODE...\n\n"); 
}

void command_help(const std::string& command) {
  listCommands();
}

void command_ping(const std::string& command) {
  printf("\npong!\n");
}

void command_cls(const std::string& command) {
  system("cls");     // @CleanUp: NOT PRETTY! We should log to our own console instead
}

glm::vec2 startSize;

Console::Console(Window* window) : window(window) {
  CONSOLE_COMMANDS(
    ConsoleCommand{command_play,  "play"},
    ConsoleCommand{command_stop,  "stop"},
    ConsoleCommand{command_help,  "help"},
    ConsoleCommand{command_ping,  "ping"},
    ConsoleCommand{command_cls,  "cls"}
  );
  
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
    parseCommand(text->text);
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

Console::~Console() {
  delete text;
  delete topBar;
  delete panel;
}

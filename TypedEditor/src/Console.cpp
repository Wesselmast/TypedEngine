#include "Console.h"

#include "Rendering/Text.h"
#include "Rendering/Quad.h"
#include "Input/Input.h"

#include "Window/Window.h"
#include <string>

#include "Rendering/Rendercommand.h"
#include "Scripting/LuaCommand.h"

#include <future>

#include "ConsoleCommands.h"
#include "Core/LevelCommand.h"

std::future<void> luaFuture;

Window* command_window;

void command_play(char** arguments) {
  //luaFuture = std::async(std::launch::async, &LuaCommand::run);             //@Volatile: Async works, but textures dont render, also race conditions?!          
  if(!LuaCommand::run()) {
    RenderCommand::removeTagged(Tag::PLAY_MODE);
    LuaCommand::quit();
  }
}

void command_stop(char** arguments) {
  // @CleanUp: Add condition to quit command. Nothing should happend if quitting fails
  RenderCommand::removeTagged(Tag::PLAY_MODE);
  LuaCommand::quit();
}

void command_help(char** arguments) {
  listCommands();
}

void command_exit(char** arguments) {
  command_window->close();
}

void command_ping(char** arguments) {
  printf("\npong!\n");
}

void command_cls(char** arguments) {
  system("cls");     // @CleanUp: NOT PRETTY! We should log to our own console instead
}

void command_echo(char** arguments) {
  printf("\n%s\n", arguments[0]);
}

void command_save_level(char** arguments) {
  LevelCommand::saveLevel(arguments[0]);
}

void command_load_level(char** arguments) {
  LevelCommand::loadLevel(arguments[0]);
}

void command_push(char** arguments) {
  LuaCommand::push(arguments[0]);
}

void command_renderinfo(char** arguments) {
  RenderCommand::print();
}

void command_printfiles(char** arguments) {
  LuaCommand::printfiles();
}

glm::vec2 startSize;

Console::Console(Window* window) : window(window) {
  CONSOLE_COMMANDS(
    ConsoleCommand{ command_play,        "play"           },
    ConsoleCommand{ command_stop,        "stop"           },
    ConsoleCommand{ command_help,        "help"           },
    ConsoleCommand{ command_ping,        "ping"           },
    ConsoleCommand{ command_cls,         "cls"            },
    ConsoleCommand{ command_exit,        "exit"           },
    ConsoleCommand{ command_echo,        "echo",       1  },
    ConsoleCommand{ command_push,        "push",       1  },
    ConsoleCommand{ command_save_level,  "save",       1  },
    ConsoleCommand{ command_load_level,  "open",       1  },
    ConsoleCommand{ command_printfiles,  "printf"         },
    ConsoleCommand{ command_renderinfo,  "printr"         } 
 );
  
  command_window = window;
  
  text = new Text("");
  text->tag = Tag::PERMANENT;
  text->useScreenPosition(true);
  text->transform.scale = { 0.75f, 0.75f };
  text->color = {220 / 255.0f, 220 / 255.0f, 204 / 255.0f, 1.0f};

  topText = new Text("console");
  topText->tag = Tag::PERMANENT;
  topText->useScreenPosition(true);
  topText->transform.scale = { 0.66f, 0.66f };
  topText->color = {240 / 255.0f, 223 / 255.0f, 175 / 255.0f, 1.0f};
  
  panel = new Quad({ 63/255.0f, 63/255.0f, 63/255.0f, 1.0f });
  panel->tag = Tag::PERMANENT;
  panel->useScreenPosition(true);

  topBar = new Quad({ 48/255.0f, 48/255.0f, 48/255.0f, 1.0f });
  topBar->tag = Tag::PERMANENT;
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
    parseCommand(text->text.c_str());
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
  delete topText;
  delete topBar;
  delete panel;
}

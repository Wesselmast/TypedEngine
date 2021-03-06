#include "Console.h"

#include "Rendering/Text.h"
#include "Rendering/Quad.h"
#include "Rendering/Sprite.h"
#include "Input/Input.h"

#include "Window/Window.h"
#include <string>

#include "Rendering/Rendercommand.h"
#include "Scripting/LuaCommand.h"
#include "Core/Utility.h"

#include <future>

#include "ConsoleCommands.h"
#include "Core/LevelCommand.h"

//std::future<void> luaFuture;

Window* command_window;

bool Console::playMode = false;
static Console* currentConsole;

void command_play(char** arguments) {
  Console::playMode = LuaCommand::run();
  currentConsole->setHidden(true);
  
  if(!Console::playMode) {
    RenderCommand::removeTagged(Tag::PLAY_MODE);
    LuaCommand::quit();
  }
}

void command_stop(char** arguments) {
  // @CleanUp: Add condition to quit command. Nothing should happend if quitting fails
  Console::playMode = false;
  RenderCommand::removeTagged(Tag::PLAY_MODE);
  LuaCommand::quit();
}

void command_sprite(char** arguments) {
  if(!Console::playMode) {
    new Sprite(arguments[0]);
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

void command_quad(char** arguments) {
  if(!Console::playMode) {
    new Quad(hexToColor(arguments[0]));  
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

void command_text(char** arguments) {
   if(!Console::playMode) {
     new Text(arguments[0], hexToColor(arguments[1]));
   }
   else {
     printf("this command is not usable in play mode!\n");
   }
}

void command_help(char** arguments) {
  if(arguments[0]) {
    listCommand(arguments[0]);
    return;
  }
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
  printf("\n");
  for(int i = 0; i < 99; i++) {
    if(arguments[i]) {
      printf("%s ", arguments[i]);
    }
    else {
      break;
    }
  }
  printf("\n");
}

void command_save_level(char** arguments) {
  if(!Console::playMode) {
    LevelCommand::saveLevel(arguments[0]);
  }
  else {
    printf("Cannot save the level while in play mode!\n");
  }
}

void command_load_level(char** arguments) {
  if(!Console::playMode) {
    LuaCommand::push(arguments[0]);
    LevelCommand::loadLevel(arguments[0]);
  }
  else {
    printf("Cannot open other levels while in play mode!\n");
  }
}

void command_renderinfo(char** arguments) {
  RenderCommand::print();
}

void command_printfiles(char** arguments) {
  LuaCommand::printfiles();
}

void command_delete(char** arguments) {
  if(!Console::playMode) {
    std::vector<Entity*> entities;
    RenderCommand::getTagged(Tag::LEVEL, &entities);
    if(arguments[0]) {
      if(!strcmp(arguments[0], "all")) {
	for(auto e : entities) delete e;
      }
      else {
	printf("ERROR: '%s' is not a valid argument for delete\n", arguments[0]);
      }
      return;
    }
    for(auto e : entities) {
      if(e->clicked) {
	delete e;
	return;
      }
    }
    printf("ERROR: No entity is selected\n");
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

void command_size(char** arguments) {
  if(!Console::playMode) {
    std::vector<Entity*> entities;
    RenderCommand::getTagged(Tag::LEVEL, &entities);
    for(auto e : entities) {
      if(e->clicked) {
	e->transform.scale = {
          stringToFloat(arguments[0]),
	  stringToFloat(arguments[1])
	};
	return;
      }
    }
    printf("ERROR: No entity is selected\n");
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

void command_position(char** arguments) {
  if(!Console::playMode) {
    std::vector<Entity*> entities;
    RenderCommand::getTagged(Tag::LEVEL, &entities);
    for(auto e : entities) {
      if(e->clicked) {
	e->transform.position = {
          stringToFloat(arguments[0]),
          stringToFloat(arguments[1])
	};
	return;
      }
    }
    printf("ERROR: No entity is selected\n");
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

void command_rotation(char** arguments) {
  if(!Console::playMode) {
    std::vector<Entity*> entities;
    RenderCommand::getTagged(Tag::LEVEL, &entities);
    for(auto e : entities) {
      if(e->clicked) {
	e->transform.rotation = stringToFloat(arguments[0]);
	return;
      }
    }
    printf("ERROR: No entity is selected\n");
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}


void command_add(char** arguments) {
  if(!Console::playMode) {
    std::vector<Entity*> entities;
    RenderCommand::getTagged(Tag::LEVEL, &entities);
    for(auto e : entities) {
      if(e->clicked) {
	if(!strcmp(arguments[0], "pos")) {
	  if(!arguments[2]) {
	    printf("ERROR: '%s' needs 2 arguments!\n", arguments[0]);
	    return;
	  }
	  e->transform.position.x += stringToFloat(arguments[1]);
	  e->transform.position.y += stringToFloat(arguments[2]);
	}
	else if(!strcmp(arguments[0], "rot")) {
	  if(arguments[2]) {
	    printf("ERROR: '%s' needs 1 argument!\n", arguments[0]);
	    return;
	  }
	  e->transform.rotation += stringToFloat(arguments[1]);
	}
	else if(!strcmp(arguments[0], "size")) {
	  if(!arguments[2]) {
	    printf("ERROR: '%s' needs 2 arguments!\n", arguments[0]);
	    return;
	  }
	  e->transform.scale.x += stringToFloat(arguments[1]);
	  e->transform.scale.y += stringToFloat(arguments[2]);
	}
	else {
	  printf("ERROR: '%s' is not a valid argument for add\n", arguments[0]);
	}
	return;
      }
    }
    printf("ERROR: No entity is selected\n");
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

void command_copy(char** arguments) {
  if(!Console::playMode) {
    std::vector<Entity*> entities;
    RenderCommand::getTagged(Tag::LEVEL, &entities);
    for(auto e : entities) {
      if(e->clicked) {
	switch(e->typeID()) {
	case 0: break;
	case 1: new Sprite(e->transform, ((Sprite*)e)->textureName); break;
	case 2: new Quad(e->transform, ((Quad*)e)->color); break;
	}
	return;
      }
    }
    printf("ERROR: No entity is selected\n");
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

void command_zoff(char** arguments) {
  if(!Console::playMode) {
    std::vector<Entity*> entities;
    RenderCommand::getTagged(Tag::LEVEL, &entities);
    for(auto e : entities) {
      if(e->clicked) {
	e->transform.zOffset = (int)stringToFloat(arguments[0]);
	return;
      }
    }
    printf("ERROR: No entity is selected\n");
  }
  else {
    printf("this command is not usable in play mode!\n");
  }
}

glm::vec2 startSize;

Console::Console(Window* window) : window(window) {
  CONSOLE_COMMANDS(
    ConsoleCommand{ command_play,	 "play",       0, 0, "Enters play mode."                                                   },
    ConsoleCommand{ command_stop,	 "stop",       0, 0, "Stops play mode."                                                    },
    ConsoleCommand{ command_help,	 "help",       0, 1, "Lists some helpful commands! Can also just list one"                 },
    ConsoleCommand{ command_ping,	 "ping",       0, 0, "Pong!"	                                                           },
    ConsoleCommand{ command_cls,	 "cls",	       0, 0, "Clears the terminal"                                                 },
    ConsoleCommand{ command_exit,	 "exit",       0, 0, "Exits the application"                                               },
    ConsoleCommand{ command_echo,	 "echo",       1, 99,"Print some words to the terminal!"                                   },
    ConsoleCommand{ command_save_level,	 "save",       1, 1, "Saves the current level and gives it this name"                      },
    ConsoleCommand{ command_load_level,	 "open",       1, 1, "Opens a level by name and destroys the current one"                  },
    ConsoleCommand{ command_sprite,	 "sprite",     1, 1, "Creates a sprite entity. Input: texture path"                        },
    ConsoleCommand{ command_quad,	 "quad",       1, 1, "Creates a quad entity. Input: color in hex"                          },
    ConsoleCommand{ command_text,	 "text",       2, 2, "Creates a text entity. Input: text and color in hex"                 },
    ConsoleCommand{ command_printfiles,	 "printf",     0, 0, "Prints all the active lua scripts"                                   },
    ConsoleCommand{ command_renderinfo,	 "printr",     0, 0, "Prints all the actives entities in the scene"                        }, 
    ConsoleCommand{ command_delete,	 "delete",     0, 1, "Deletes selected entity. Add 'all' to delete everything"             }, 
    ConsoleCommand{ command_size,	 "size",       2, 2, "Sets the size of the selected entity"                                },
    ConsoleCommand{ command_position,	 "pos",	       2, 2, "Sets the position of the selected entity"                            },
    ConsoleCommand{ command_rotation,	 "rot",	       1, 1, "Sets the rotation of the selected entity"                            }, 
    ConsoleCommand{ command_add,	 "add",	       2, 3, "Adds transformation to selected entity, add flag 'pos, rot or size'" },
    ConsoleCommand{ command_zoff,	 "zoff",       1, 1, "Gives the object a z offset from the rest of the objects"            },
    ConsoleCommand{ command_copy,	 "cpy",	       0, 0, "Copies the selected entity"                                          } 
 );
  
  currentConsole = this;
  command_window = window;

  text = new Text("");
  text->tag = Tag::PERMANENT;
  text->useScreenPosition(true);
  text->transform.zOffset = 30;
  text->transform.scale = { 0.75f, 0.75f };
  text->color = {220 / 255.0f, 220 / 255.0f, 204 / 255.0f, 1.0f};

  topText = new Text("console");
  topText->tag = Tag::PERMANENT;
  topText->useScreenPosition(true);
  topText->transform.zOffset = 30;
  topText->transform.scale = { 0.66f, 0.66f };
  topText->color = {240 / 255.0f, 223 / 255.0f, 175 / 255.0f, 1.0f};
  
  panel = new Quad({ 63/255.0f, 63/255.0f, 63/255.0f, 1.0f });
  panel->transform.zOffset = 28;
  panel->tag = Tag::PERMANENT;
  panel->useScreenPosition(true);

  topBar = new Quad({ 48/255.0f, 48/255.0f, 48/255.0f, 1.0f });
  topBar->transform.zOffset = 29;
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

void Console::setHidden(bool hidden) {
  text->hidden = hidden;
  topBar->hidden = hidden;
  topText->hidden = hidden;
  panel->hidden = hidden;
  this->hidden = hidden;
}

bool Console::getHidden() const {
  return hidden;
}

void Console::recieveKey(Key key, Modifier mod) {
  bool inputToLua = playMode & getHidden();
  if(inputToLua) {
    LuaCommand::input(key);
    return;
  }

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
  if(key == Key::SHIFT) return;
  text->text.push_back((char)Input::convertKey(key, mod));
}

Console::~Console() {
  delete text;
  delete topText;
  delete topBar;
  delete panel;
}

#include "App.h"

#include "Core/Transform.h"
#include "Rendering/Sprite.h"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

glm::vec2 position = glm::vec3(0, 0, 0);
const float zoomSpeed = 0.5f;
const float panSpeed = 750.0f;

bool checkLua(lua_State* L, int result) {
  if (result != LUA_OK) {
    std::cout << lua_tostring(L, -1) << std::endl;
    return false;
  }
  return true;
}


// ToDo: @CleanUp: Move rendercommands to main file (main should handle all rendering, this should handle other stuff)
void App::begin() {
  treeSprite = new Sprite("res/textures/T_Tree.png"); 
  treeSprite->transform.position = { 1000, 1250 };

  //ToDo @Optimization: check if transforms are in camera viewport (if not, cull them)
  for (int i = 0; i < 2; i++) {
    new Sprite({{ 1024.0f * i, 0.0f }, 0.0f, { 1.0f, 1.0f}});
  }

  //LUA SCOPE
  {
    struct Vector2D {
      static int createVector2D(lua_State* L) {
	lua_newtable(L);
	lua_pushstring(L, "x");
	lua_pushnumber(L, 0);
	lua_settable(L, -3);
	
	lua_pushstring(L, "y");
	lua_pushnumber(L, 0);
	lua_settable(L, -3);
	
	// pops off everything but table
	
	luaL_getmetatable(L, "Vector_M");
	lua_setmetatable(L, -2);
	
	// pops off metatable 
	
	return 1;
      }
      
      static int __add(lua_State* L) {
	lua_pushstring(L, "x");
	lua_gettable(L, -3);
	lua_Number xL = lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_pushstring(L, "x");
	lua_gettable(L, -2);
	lua_Number xR = lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_pushstring(L, "y");
	lua_gettable(L, -3);
	lua_Number yL = lua_tonumber(L, -1);
	lua_pop(L, 1);
	lua_pushstring(L, "y");
	lua_gettable(L, -2);
	lua_Number yR = lua_tonumber(L, -1);
	lua_pop(L, 1);
	
	createVector2D(L);
	
	lua_pushstring(L, "x");
	lua_pushnumber(L, xL + xR);
	lua_rawset(L, -3);	//just sets the table, but doesn't call metamethods
	
	lua_pushstring(L, "y");
	lua_pushnumber(L, yL + yR);
	lua_rawset(L, -3);
	
	return 1;
      }
    };
    
    auto setLuaPath = [](lua_State* L, const char* path) -> int {
			lua_getglobal(L, "package");
			lua_getfield(L, -1, "path");
			std::string c_path = lua_tostring(L, -1);
			c_path.append(";");
			c_path.append(path);
			c_path.append("\\?.lua");
			lua_pop(L, 1);
			lua_pushstring(L, c_path.c_str());
			lua_setfield(L, -2, "path");
			lua_pop(L, 1);
			return 0;
		      };
    
    
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    
    lua_pushcfunction(L, Vector2D::createVector2D);
    lua_setglobal(L, "createVector");
    
    luaL_newmetatable(L, "Vector_M");
    lua_pushstring(L, "__add"); //these are specially named, look them up!
    lua_pushcfunction(L, Vector2D::__add);
    lua_settable(L, -3); //because there are 2 other things pushed on
    
    std::string dir;
    char buf[256];
    GetCurrentDirectoryA(256, buf);
    dir.append(buf);
    dir.append("\\..\\TypedGame\\src");
    setLuaPath(L, dir.c_str());
    
    if (checkLua(L, luaL_dofile(L, "../TypedGame/src/test.lua"))) {
      
      lua_getglobal(L, "main");
      
      if (lua_isfunction(L, -1)) {
	checkLua(L, lua_pcall(L, 0, 0, 0));
      }
    }
    
    lua_close(L);
  }
}

void App::tick(float deltaTime, float time) {
  position += input * deltaTime * zoom * panSpeed;
  camera->setPosition(position);
  camera->setScale(glm::vec2(zoom));
  
  treeSprite->transform.scale.x = glm::sin(time);
}

void App::onKeyPressed(Key key, Modifier mod) {
  switch (key) {
  case Key::W: input.y =  1.0f; break;
  case Key::A: input.x = -1.0f; break;
  case Key::S: input.y = -1.0f; break;
  case Key::D: input.x =  1.0f; break;
  case Key::ESCAPE: window->close(); break;
  }
}

void App::onKeyReleased(Key key, Modifier mod) {
  switch (key) {
  case Key::W: input.y =  0.0f; break;
  case Key::A: input.x = -0.0f; break;
  case Key::S: input.y = -0.0f; break;
  case Key::D: input.x =  0.0f; break;
  }
}

void App::onMouseScrolled(float offsetX, float offsetY) {
  zoom += -offsetY * zoomSpeed;
  if (zoom <= 0.01f) {
    zoom = 0.1f;
  }
  else if (zoom >= 10) {
    zoom = 10;
  }
}

Application* createApplication() {
  return new App();
}

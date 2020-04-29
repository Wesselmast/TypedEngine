#include "TElua.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdbool.h> 

extern int luaopen_TEcore(lua_State* L);

#ifndef LUA_EXTRALIBS
#define LUA_EXTRALIBS
#endif

static bool closedLua = false;

static const luaL_Reg lualibs[] = {
  {"TEcore", luaopen_TEcore},
  LUA_EXTRALIBS
  {NULL, NULL}
};

void openLibs(lua_State* L) {
  const luaL_Reg *lib = lualibs;
  for (; lib->func; lib++) {
    lib->func(L);
    lua_settop(L, 0);
  }
}

static lua_State* L = NULL;

void init_lua() {
  L = luaL_newstate();
  luaL_openlibs(L);
  openLibs(L);

  char buf[256];
  GetCurrentDirectoryA(256, buf);
  
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "path");
  
  char path[1024];
  strcpy(path, (const char*)lua_tostring(L, -1));
  strcat(path, ";");
  strcat(path, buf);
  strcat(path, "\\gamefiles\\?.lua");
  lua_pop(L, 1);
  
  lua_pushstring(L, path);
  lua_setfield(L, -2, "path");
  lua_pop(L, 1);
  

  lua_getglobal(L, "package");
  lua_getfield(L, -1, "cpath");
  
  char dllpath[1024];
  strcpy(dllpath, (const char*)lua_tostring(L, -1));
  strcat(dllpath, ";");
  strcat(dllpath, buf);
  strcat(dllpath, "\\lib\\?\\?.dll");
  lua_pop(L, 1);
  
  lua_pushstring(L, dllpath);
  lua_setfield(L, -2, "cpath");
  lua_pop(L, 1);
  
  char mainFile[256];
  strcat(mainFile, buf);
  strcat(mainFile, "\\gamefiles\\main.lua");

  if (luaL_dofile(L, mainFile) != LUA_OK) {
    printf("%s\n", lua_tostring(L, -1));
    return;
  }
}

void compile_lua() {
  if(closedLua) return;

  lua_getglobal(L, "main");
  
  if (lua_isfunction(L, -1)) {
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      printf("%s\n", lua_tostring(L, -1));
      return;
    }
  }
}

void close_lua() {
  if(closedLua) return;
  closedLua = true;
  lua_close(L);
}

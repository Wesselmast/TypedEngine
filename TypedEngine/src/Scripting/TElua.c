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
static bool compiled = false;
char mainFile[256];

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
  
  strcat(mainFile, buf);
  strcat(mainFile, "\\gamefiles\\main.lua");
}

void compile_lua() {
  if(closedLua) return;
  if(compiled) {
    printf("ERRORo: Already running!\n");
    return;
  }
  
  if (luaL_dofile(L, mainFile) != LUA_OK) {
    printf("%s\n", lua_tostring(L, -1));
    return;
  }

  lua_getglobal(L, "begin");
  
  if (lua_isfunction(L, -1)) {
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      printf("%s\n", lua_tostring(L, -1));
      return;
    }
  }

  compiled = true;
}

void run_lua(float deltaTime, float time) {
  if(closedLua || !compiled) return;

  lua_getglobal(L, "tick");
  
  if (lua_isfunction(L, -1)) {
    lua_pushnumber(L, deltaTime);
    lua_pushnumber(L, time);
    if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
      printf("%s\n", lua_tostring(L, -1));
      return;
    }
  }
}

void quit_lua() {
  compiled = false;
}

void close_lua() {
  if(closedLua) return;
  closedLua = true;
  lua_close(L);
}

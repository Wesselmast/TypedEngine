#include "SwigExample.h"

//extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
//}

#include <stdio.h>
#include <stdbool.h>

extern int luaopen_TypedLuaCollection(lua_State* L);

#ifndef LUA_EXTRALIBS
#define LUA_EXTRALIBS	/* empty */
#endif


static const luaL_Reg lualibs[] = {
  {"base", luaopen_base},
  {"table", luaopen_table},
  {"io", luaopen_io},
  {"string", luaopen_string},
  {"math", luaopen_math},
  {"debug", luaopen_debug},
  /* add your libraries here */
  {"TypedLuaCollection", luaopen_TypedLuaCollection},
  LUA_EXTRALIBS
  {NULL, NULL}
};

void openLibs(lua_State* L) {
  const luaL_Reg *lib = lualibs;
  for (; lib->func; lib++) {
    lib->func(L);  /* open library */
    lua_settop(L, 0);  /* discard any results */
  }
}


//void SwigExample::run() {
void run_lua() {
  //	printf("hi");

  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  openLibs(L);

  char buf[256];
  GetCurrentDirectoryA(256, buf);
  char folder[] = "\\gamefiles";
  strcat(buf, folder);
  
  // BEGIN LUA PATH
  
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "path");
  
  char path[1024];
  strcpy(path, (const char*)lua_tostring(L, -1));
  strcat(path, ";");
  strcat(path, buf);
  strcat(path, "\\?.lua");
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
  strcat(dllpath, "\\..\\..\\TypedLuaCollection\\?.dll");
  lua_pop(L, 1);
  
  lua_pushstring(L, dllpath);
  lua_setfield(L, -2, "cpath");
  lua_pop(L, 1);
  
  // END LUA PATH
  
  char mainFile[] = "\\test.lua";
  strcat(buf, mainFile);
  
  if (luaL_dofile(L, buf) != LUA_OK) {
    printf("%s\n", lua_tostring(L, -1));
    return;
  }
  lua_getglobal(L, "main");
  
  if (lua_isfunction(L, -1)) {
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      printf("%s\n", lua_tostring(L, -1));
      return;
    }
  }
  lua_close(L);
  return;
}

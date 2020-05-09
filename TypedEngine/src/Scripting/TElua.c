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

struct LuaFile {
  char fileName[128];
  int address;
};

static struct LuaFile* luafiles[256 * sizeof(struct LuaFile*)];

static unsigned char closedLua = 0;
static unsigned char compiled = 0;
char filePath[256];

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
  
  strcat(filePath, buf);
  strcat(filePath, "\\gamefiles\\");
}


void push_lua(char* file) {
  if(compiled || closedLua) return;

  static int index = 0;
  file[strlen(file)+1] = '\0';

  luafiles[index] = malloc(sizeof(struct LuaFile));  

  strcpy(luafiles[index]->fileName, filePath);
  strcat(luafiles[index]->fileName, file);

  /* printf("%s\n", luafiles[index]->fileName); */
  
  if (luaL_dofile(L, luafiles[index]->fileName/*luafiles[index]->fileName*/) != LUA_OK) {
    printf("%s\n", lua_tostring(L, -1));
    return;
  }

  lua_getglobal(L, "object");
  luafiles[index]->address = luaL_ref(L, LUA_REGISTRYINDEX);
  printf("%d\n", luafiles[index]->address);

  index++;
}

void print_lua_files() {
  printf("Lua Files:\n");
  for(int i = 0; i < sizeof(luafiles) / sizeof(struct LuaFile*); i++) {
    if(!luafiles[i]) break;
    printf("   %d = %s\n", i, luafiles[i]->fileName);
  }
  printf("\n");
}

void run_lua() {
  if(closedLua) return;
  if(compiled) {
    printf("ERROR: Already running!\n");
    return;
  }

  for(int i = 0; i < sizeof(luafiles) / sizeof(struct LuaFile*); i++) {
    if(!luafiles[i]) break;
    
    lua_rawgeti(L, LUA_REGISTRYINDEX, luafiles[i]->address);
    lua_getfield(L, -1, "begin");
    
    if (lua_isfunction(L, -1)) {
      if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
	printf("%s\n", lua_tostring(L, -1));
	return;
      }
    }
  }
  
  compiled = true;
}

void tick_lua(float deltaTime, float time) {
  if(closedLua || !compiled) return;
  
  for(int i = 0; i < sizeof(luafiles) / sizeof(struct LuaFile*); i++) {
    if(!luafiles[i]) break;

    lua_rawgeti(L, LUA_REGISTRYINDEX, luafiles[i]->address);
    lua_getfield(L, -1, "tick");
    
    if (lua_isfunction(L, -1)) {
      lua_pushnumber(L, deltaTime);
      lua_pushnumber(L, time);
      if (lua_pcall(L, 2, 0, 0) != LUA_OK) {
  	printf("%s\n", lua_tostring(L, -1));
  	return;
      }
    }
  }
  
  
/*   if (luaL_dofile(L, luafiles[0]) != LUA_OK) {  */
/*     printf("%s\n", lua_tostring(L, -1));  */
/*     return;  */
/*   } */
  
/*   lua_getglobal(L, "tick");  */
  
/*   if (lua_isfunction(L, -1)) {  */
/*     lua_pushnumber(L, deltaTime);  */
/*     lua_pushnumber(L, time);  */
/*     if (lua_pcall(L, 2, 0, 0) != LUA_OK) {  */
/*       printf("%s\n", lua_tostring(L, -1));  */
/*       return;  */
/*     }  */
/*   }  */
/* } */
}
void quit_lua() {
  compiled = false;
}

void close_lua() {
  if(closedLua) return;
  closedLua = true;
  closedLua = 1;
  lua_close(L);
}

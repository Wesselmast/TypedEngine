#include "TElua.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#include <string.h>
#include <stdio.h>

extern int luaopen_TEcore(lua_State* L);

#ifndef LUA_EXTRALIBS
#define LUA_EXTRALIBS
#endif

struct LuaFile {
  char fileName[128];
  int address;
};

//static struct LuaFile* luafiles[256 * sizeof(struct LuaFile*)];
static char currentFile[1024];

static unsigned char closedLua = 0;
static unsigned char compiled = 0;
char filePath[256];

static const luaL_Reg lualibs[] = {
  {"TEcore", luaopen_TEcore},
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
  strcat(path, "\\scripts\\?.lua");
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
  strcat(filePath, "\\scripts\\");
}

void push_lua(char* file) {
  if(closedLua) return;
  if(compiled) {
    printf("ERROR: Can't push lua file whilst in play mode!\n");
    return;
  }
  
  char fileBuffer[128];
  strcpy(fileBuffer, file);
  strcat(fileBuffer, ".lua");
  fileBuffer[strlen(file)+5] = '\0';
  
  //  currentFile = malloc(sizeof(struct LuaFile));  

  strcpy(currentFile, filePath);
  strcat(currentFile, fileBuffer);

  FILE* l_file;
  if ((l_file = fopen(currentFile, "r"))) {
    fclose(l_file);
    return;
  }
  fclose(l_file);
  l_file = fopen(currentFile, "w");

  fputs("require 'TEcore'\n\n", l_file);
  fputs("function begin()\n", l_file);
  fputs("   print('Hello, World!')\n", l_file);
  fputs("end\n\n", l_file);
  fputs("function tick(deltaTime)\n", l_file);
  fputs("end\n\n", l_file);

  printf("Created %s because it didn't exist!", currentFile);
  fclose(l_file);
}

/* void pop_lua(char* file) { */
/*   if(closedLua) return; */
  
/* } */

void print_lua_files() {
/*   printf("Lua Files:\n"); */
/*   for(int i = 0; i < sizeof(luafiles) / sizeof(struct LuaFile*); i++) { */
/*     if(!luafiles[i]) break; */
/*     printf("   %d = %s\n", i, luafiles[i]->fileName); */
/*   } */
/*   printf("\n"); */
}

int run_lua() {
  if(closedLua) return 1;
  if(compiled) {
    printf("ERROR: Already running!\n");
    return 0;
  }

  if(strlen(currentFile) == 0) {
    printf("ERROR: Aborting, trying to enter play mode without a lua file!\n");
    return 0;
  }

  if (luaL_dofile(L, currentFile) != LUA_OK) {
    printf("ERROR: %s\n", lua_tostring(L, -1));
    return 0;
  }
  
  printf("\nENTERING PLAY MODE...\n\n");

  lua_getglobal(L, "begin");
  
  if (lua_isfunction(L, -1)) {
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
      printf("ERROR: %s\n", lua_tostring(L, -1));
      return 0;
    }
  }
  
  compiled = 1;
  return compiled;
}

void tick_lua(float deltaTime, float time) {
  if(closedLua || !compiled || !currentFile) return;
  
  lua_getglobal(L, "tick");
  
  if (lua_isfunction(L, -1)) {
    lua_pushnumber(L, deltaTime);
    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
      printf("%s\n", lua_tostring(L, -1));
      return;
    }
  }
}

void input_lua(const char* input) {
  if(closedLua || !compiled || !currentFile) return;
  
  lua_getglobal(L, "key_down");
  
  if (lua_isfunction(L, -1)) {
    lua_pushstring(L, input);
    if (lua_pcall(L, 1, 0, 0) != LUA_OK) {
      printf("%s\n", lua_tostring(L, -1));
      return;
    }
  }
}

void quit_lua() {
  if(!compiled) {
    printf("ERROR: Can't stop when you're not running!\n");
    return;
  }
  compiled = 0;
  printf("\nENTERING EDITOR MODE...\n\n"); 
}

void close_lua() {
  if(closedLua) return;
  closedLua = 1;
  lua_close(L);
}

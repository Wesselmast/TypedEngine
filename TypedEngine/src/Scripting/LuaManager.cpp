#include "LuaManager.h"

extern "C" {
  #include "Scripting/TElua.h"
}

void LuaManager::initLua() {
  init_lua();
}

int LuaManager::runLua() {
  return run_lua();
}

void LuaManager::pushLua(char* file) {
  push_lua(file);
}

void LuaManager::printLuaFiles() {
  print_lua_files();
}

void LuaManager::closeLua() {
  close_lua();
}

void LuaManager::tickLua(float deltaTime, float time) {
  tick_lua(deltaTime, time);
}

void LuaManager::quitLua() {
  quit_lua();
}

void LuaManager::inputLua(const char* input) {
  input_lua(input);
} 

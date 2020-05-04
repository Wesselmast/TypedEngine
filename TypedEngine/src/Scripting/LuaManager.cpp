#include "PCH.h"

#include "LuaManager.h"

extern "C" {
  #include "Scripting/TElua.h"
}

void LuaManager::initLua() {
  init_lua();
}

void LuaManager::runLua() {
  run_lua();
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


#pragma once

#include "LuaManager.h"

class LuaCommand {
 public:
  inline static void init() {
    lua->initLua();
  }

  inline static int run() {
    return lua->runLua();
  }

  inline static void push(char* file) {
    lua->pushLua(file);
  }
    
  inline static void printfiles() {
    lua->printLuaFiles();
  }

  inline static void close() {
    lua->closeLua();
  }

  inline static void tick(float deltaTime, float time) {
    lua->tickLua(deltaTime, time);
  }

  inline static void quit() {
    lua->quitLua();
  }
 private:
  static LuaManager* lua;
};

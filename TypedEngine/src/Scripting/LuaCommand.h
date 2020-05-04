#pragma once

#include "LuaManager.h"

class LuaCommand {
 public:
  inline static void init() {
    lua->initLua();
  }

  inline static void run() {
    lua->runLua();
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

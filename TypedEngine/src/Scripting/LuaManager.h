#pragma once

class LuaManager {
 public:
  LuaManager() {}

  void initLua();
  void runLua();
  void pushLua(char* file);
  void printLuaFiles();
  void closeLua();
  void tickLua(float deltaTime, float time);
  void quitLua();
};

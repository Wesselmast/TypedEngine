#pragma once

class LuaManager {
 public:
  LuaManager() {}

  void initLua();
  void runLua();
  void closeLua();
  void tickLua(float deltaTime, float time);
  void quitLua();
};

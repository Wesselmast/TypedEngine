#pragma once

#include "LevelManager.h"

class LevelCommand {
 public:
  inline static void saveLevel(char* path) {
    levelManager->saveLevel(path);
  }
  
  inline static void loadLevel(char* path) {
    levelManager->loadLevel(path);
  }
  
 private:
  static LevelManager* levelManager;
};

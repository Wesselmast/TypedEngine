#pragma once

#include "LevelManager.h"

class LevelCommand {
 public:
  inline static int saveLevel(char* path) {
    return levelManager->saveLevel(path);
  }
  
  inline static int loadLevel(char* path) {
    return levelManager->loadLevel(path);
  }
  
 private:
  static LevelManager* levelManager;
};

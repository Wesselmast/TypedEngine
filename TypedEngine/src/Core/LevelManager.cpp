#include "LevelManager.h"

#include "Rendering/RenderCommand.h"
#include "Entity.h"

#include <string.h>
#include <stdio.h>

#include <vector>
#include <fstream>

#ifdef _WIN32
#include <Windows.h>
#endif

void LevelManager::saveLevel(char* path) {
  char buf[1024];
  GetCurrentDirectoryA(256, buf);
  strcat(buf, "\\levels\\");
  strcat(buf, path);
  strcat(buf, ".TELevel");
  
  std::ofstream file(buf, std::ios::out | std::ios::binary);
  if(!file) {
    printf("Cannot open file %s!", buf);
    return;
  }

  std::vector<Entity*> entities;  
  RenderCommand::getTagged(Tag::LEVEL, &entities);

  for(int i = 0; i < entities.size(); i++) {
    file.write((char*)entities[i], entities[i]->size());
  }
  file.close();
  if(!file.good()) {
    printf("Couldn't write to file %s!", buf);
    return;
  }
}


void LevelManager::loadLevel(char* path) {
  char buf[1024];
  GetCurrentDirectoryA(256, buf);
  strcat(buf, "\\levels\\");
  strcat(buf, path);
  strcat(buf, ".TELevel");
  
  std::ifstream file(buf, std::ios::out | std::ios::binary);
  if(!file) {
    printf("Cannot open file %s!", buf);
    return;
  }

  // @ToDo: FIGURE THIS OUT!


  // std::vector<Entity*> entities;
  // entities.resize(3);
  // for(int i = 0; i < 3; i++) {
  //   file.read((char*)entities[i], entities[i]->size());
  // }


  file.close();
  if(!file.good()) {
    printf("Couldn't write to file %s!", buf);
    return;
  }
}

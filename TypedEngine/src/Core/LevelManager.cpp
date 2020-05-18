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

  std::ios_base::sync_with_stdio(false);
  std::ofstream file(buf, std::ios::out | std::ios::binary );
  if(!file) {
    printf("Cannot open file %s!\n", buf);
    return;
  }

  std::vector<Entity*> entities;  
  RenderCommand::getTagged(Tag::LEVEL, &entities);
  
  
  for(int i = 0; i < entities.size(); i++) {
    int entitySize = entities[i]->size();
    int typeID = entities[i]->typeID();
    file.write((char*)&typeID, sizeof(int));
    file.write((char*)&entitySize, sizeof(int));
    file.write((char*)entities[i], entitySize);
    
    printf("%d\n", typeID);
    printf("%d\n", entitySize);
  }
  file.close();

  if(!file.good()) {
    printf("Couldn't write to file %s!\n", buf);
    return;
  }
}

template<typename T>
Entity* loadEntity(std::ifstream& file) {
  Entity* entity = new T;
    
  int offset;
  file.read((char*)&offset, sizeof(int));
  file.read((char*)entity, offset); 
  
  printf("%d\n", offset);
  return entity;
}


void LevelManager::loadLevel(char* path) {
  char buf[1024];
  GetCurrentDirectoryA(256, buf);
  strcat(buf, "\\levels\\");
  strcat(buf, path);
  strcat(buf, ".TELevel");
  
  std::ifstream file(buf, std::ios::binary);
  if(!file) {
    printf("Cannot open file %s!\n", buf);
    return;
  }

  // @ToDo: FIGURE THIS OUT!

  std::vector<Entity*> entities;

  int typeID;
  while(file.read((char*)&typeID, sizeof(int))) {
    printf("%d\n", typeID);

    switch(typeID) {
    case 0: entities.push_back(loadEntity<Text>(file));   break;
    case 1: entities.push_back(loadEntity<Sprite>(file)); break;
    case 2: entities.push_back(loadEntity<Quad>(file));   break;
    }
  }
  
  file.close();

  if(!file.good()) {
    printf("Couldn't read file %s!\n", buf);
    return;
  }
}

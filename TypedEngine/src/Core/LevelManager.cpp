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

int LevelManager::saveLevel(char* path) {
  char buf[1024];
  GetCurrentDirectoryA(256, buf);
  strcat(buf, "\\levels\\");
  strcat(buf, path);
  strcat(buf, ".TELevel");

  std::ofstream file(buf, std::ios::out | std::ios::binary );
  if(!file) {
    printf("Cannot open file %s!\n", buf);
    return 0;
  }

  std::vector<Entity*> entities;
  RenderCommand::getTagged(Tag::LEVEL, &entities);
  
  for(int i = 0; i < entities.size(); i++) {
    int entitySize = entities[i]->size();
    int typeID = entities[i]->typeID();
    file.write((char*)&typeID, sizeof(int));
    file.write((char*)&entitySize, sizeof(int));
    file.write((char*)entities[i], entitySize);
  }
  
  file.close();

  if(!file.good()) {
    printf("Couldn't write to file %s!\n", buf);
    return 0;
  }

  printf("\nDONE SAVING LEVEL!\n\n");
  return 1;
}

Sprite* loadSprite(std::ifstream& file) {
  Sprite* sprite = (Sprite*)malloc(sizeof(Sprite));

  int offset;
  file.read((char*)&offset, sizeof(int));
  file.read((char*)sprite, offset);

  return sprite;
}

Text* loadText(std::ifstream& file) {
  Text* text = (Text*)malloc(sizeof(Text));

  int offset;
  file.read((char*)&offset, sizeof(int));
  file.read((char*)text, offset); 

  new(text) Text(text->transform, text->text);
  return text;
}

template<typename T>
T* loadEntity(std::ifstream& file) {
  Entity* entity = (Entity*)malloc(sizeof(T));

  int offset;
  file.read((char*)&offset, sizeof(int));
  file.read((char*)entity, offset); 

  return (T*)entity;
}


int LevelManager::loadLevel(char* path) {
  char buf[1024];
  GetCurrentDirectoryA(256, buf);
  strcat(buf, "\\levels\\");
  strcat(buf, path);
  strcat(buf, ".TELevel");
  
  std::ifstream file(buf, std::ios::binary);
  if (!file) {
    printf("Cannot open file %s!\n", buf);
    return 0;
  }
  
  RenderCommand::removeTagged(Tag::LEVEL);

  std::vector<Sprite*> sprites;
  std::vector<Quad*> quads;
  std::vector<Text*> texts;
  
  int typeID;
  while (file.read((char*)&typeID, sizeof(int))) {
    switch (typeID) {
    case 0: texts.push_back(loadEntity<Text>(file));     break;
    case 1: sprites.push_back(loadEntity<Sprite>(file)); break;
    case 2: quads.push_back(loadEntity<Quad>(file));     break;
    }
  }
  
  file.close();
  
  for (auto& e : sprites) { 
    new(e) Sprite(e->transform, e->textureName);
  }
  for (auto& e : texts) { 
    new(e) Text(e->transform, e->text);
  }
  for (auto& e : quads) { 
    new(e) Quad(e->transform, e->color);    
  }
  // maybe this below should happen after closing the file
  
  printf("\nDONE! LEVEL CONTENTS: \n\n");
  RenderCommand::print();
  
  return 1;
}

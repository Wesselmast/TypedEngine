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

void writeSprite(std::ofstream& file, Sprite* s) {
  int len = strlen(s->textureName) + 1;
  int typeID = s->typeID();
  char* tn = s->textureName;
  file.write((char*)&typeID, sizeof(int));
  file.write((char*)s, sizeof(Sprite)); 
  file.write((char*)&len, sizeof(int));
  file.write((char*)&tn[0], len);
}

void constructSprite(std::ifstream& file) {
  Sprite* data = (Sprite*)malloc(sizeof(Sprite));
  int len = 0;
  
  file.read((char*)data, sizeof(Sprite));
  file.read((char*)&len, sizeof(int));
  
  char* tn = (char*)malloc(len);
  file.read((char*)&tn[0], len);

  new(data) Sprite(data->transform, tn);
}  

void writeQuad(std::ofstream& file, Quad* q) {
  int typeID = q->typeID();
  file.write((char*)&typeID, sizeof(int));
  file.write((char*)q, sizeof(Quad)); 
}

void constructQuad(std::ifstream& file) {
  Quad* data = (Quad*)malloc(sizeof(Quad));
  
  file.read((char*)data, sizeof(Quad));
  new(data) Quad(data->transform, data->color);
}  

void writeText(std::ofstream& file, Text* t) {
  int typeID = t->typeID();
  file.write((char*)&typeID, sizeof(int));
  file.write((char*)t, sizeof(Text)); 
}

void constructText(std::ifstream& file) {
  Text* data = (Text*)malloc(sizeof(Text));
  
  file.read((char*)data, sizeof(Text));
  new(data) Text(data->transform, data->text, data->color);
}

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
  
  for(auto e : entities) {
    switch(e->typeID()) {
    case 0: writeText(file,   (Text*)e);   break;
    case 1: writeSprite(file, (Sprite*)e); break;
    case 2: writeQuad(file,   (Quad*)e);   break;
    }
  }

  file.close();

  if(!file.good()) {
    printf("Couldn't write to file %s!\n", buf);
    return 0;
  }

  printf("\nDONE SAVING LEVEL!\n\n");
  return 1;
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

  int typeID;
  while (file.read((char*)&typeID, sizeof(int))) {
    switch(typeID) {
    case 0: constructText(file);   break;
    case 1: constructSprite(file); break;
    case 2: constructQuad(file);   break;
    }
  }

  file.close();
  printf("\nDONE! LEVEL CONTENTS: \n\n");
  RenderCommand::print();
  
  return 1;
}

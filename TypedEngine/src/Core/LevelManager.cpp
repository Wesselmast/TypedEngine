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

template<typename T>
T* loadEntity(std::ifstream& file) {
  void* entity = (void*)malloc(sizeof(T));

  int offset;
  file.read((char*)&offset, sizeof(int));
  file.read((char*)entity, offset); 

  return (T*)entity;
}


void writeSprite(std::ofstream& file, Sprite* s) {
  int len = strlen(s->textureName) + 1;
  int typeID = s->typeID();
  char* tn = s->textureName;
  file.write((char*)&typeID, sizeof(int));
  file.write((char*)s, sizeof(Sprite)); 
  file.write((char*)&len, sizeof(int));
  file.write((char*)&tn[0], len);

  printf("SIZE OF FILE : %d\n", sizeof(int) + sizeof(Sprite) + sizeof(int) + len);
}

void readSprite(std::ifstream& file) {
  Sprite* data = (Sprite*)malloc(sizeof(Sprite));
  int len = 0;
  
  file.read((char*)data, sizeof(Sprite));
  file.read((char*)&len, sizeof(int));
  
  printf("%d:::", len);
  printf("SIZE OF FILE : %d\n", sizeof(int) + sizeof(Sprite) + sizeof(int) + len);

  char* tn = (char*)malloc(len);
  file.read((char*)&tn[0], len);

  new(data) Sprite(data->transform, tn);
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
    if(e->typeID() == 1) {
      writeSprite(file, (Sprite*)e);
    }
  }


  // for(int i = 0; i < entities.size(); i++) {
  //   int entitySize = entities[i]->size();
  //   int typeID = entities[i]->typeID();
  //   file.write((char*)&typeID, sizeof(int));
  //   file.write((char*)&entitySize, sizeof(int));
  //   file.write((char*)entities[i], entitySize);
  // }
  
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

  std::vector<Sprite*> sprites;
  std::vector<Quad*> quads;
  std::vector<Text*> texts;
  
  int typeID;
  while (file.read((char*)&typeID, sizeof(int))) {
    if(typeID == 1) {
      readSprite(file);
    }
  }

    //   switch (typeID) {
  //   case 0: texts.push_back(loadEntity<Text>(file));     break;
  //   case 1: sprites.push_back(loadEntity<Sprite>(file)); break;
  //   case 2: quads.push_back(loadEntity<Quad>(file));     break;
  //   }
  // }
  
  file.close();

  //for (auto e : sprites) { 
  //  printf("%s\n", e->textureName);
  //  new(e) Sprite(e->transform, e->textureName);
  //}
  //for (auto e : texts) { 
  //  new(e) Text(e->transform, e->text);
  //}
  //for (auto e : quads) { 
  //  new(e) Quad(e->transform, e->color);    
  //}
  
  printf("\nDONE! LEVEL CONTENTS: \n\n");
  RenderCommand::print();
  
  return 1;
}

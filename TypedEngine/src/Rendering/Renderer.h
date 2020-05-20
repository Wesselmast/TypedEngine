#pragma once

#include "glm/glm.hpp"

#include <vector>
#include <string>

#include "Sprite.h"
#include "Shader.h"
#include "Text.h"
#include "Quad.h"
#include "Camera.h"

#include <stdio.h>

class Renderer {
public:
  virtual void init(Camera* camera) = 0;
  virtual void setBlending(bool enabled) = 0;
  virtual void setCulling(bool enabled) = 0;

  virtual void drawSprite(Sprite* sprite) = 0;
  virtual void drawQuad(Quad* quad) = 0;
  virtual void drawText(Text* text) = 0;
  virtual void clear(glm::vec4 color) = 0;

  virtual void run() = 0;

  virtual ~Renderer() {
    deleteVectorAll<Sprite>(&sprites);
    deleteVectorAll<Text>(&texts);
    deleteVectorAll<Quad>(&quads);    
    delete defaultTextShader;
    delete defaultSpriteShader;
    delete defaultQuadShader;
    delete camera;
  }

  template<typename T>
  inline void deleteVectorByTag(std::vector<T*>* v, Tag tag) {
    for (int i = 0; i < v->size(); i++) {
      if(!v->at(i)) break;
      if(v->at(i)->tag != tag) continue;
      delete v->at(i);
      i--;
    }
  }

  template<typename T>
  inline std::vector<T*> getVectorByTag(std::vector<T*>* v, Tag tag) {
    std::vector<T*> local_v;
    for (int i = 0; i < v->size(); i++) {
      if(v->at(i)->tag != tag) continue;
      local_v.push_back(v->at(i));
    }
    return local_v;
  }
  
  std::vector<Sprite*> sprites;
  std::vector<Text*> texts;
  std::vector<Quad*> quads;
protected:
  Shader* defaultTextShader;
  Shader* defaultSpriteShader;
  Shader* defaultQuadShader;
  Camera* camera;  
private:
  template<typename T>
  inline void deleteVectorAll(std::vector<T*>* v) {
    for (int i = 0; i < v->size(); i++) {
      delete v->at(i);
      i--;
    }
    v->clear();
  }
};

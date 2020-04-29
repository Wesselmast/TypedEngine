#pragma once

#include "glm/glm.hpp"

#include <vector>
#include <string>

#include "sprite.h"
#include "shader.h"
#include "text.h"
#include "quad.h"
#include "camera.h"

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
    deleteVector<Sprite>(&sprites);
    deleteVector<Text>(&texts);
    deleteVector<Quad>(&quads);    
    delete defaultTextShader;
    delete defaultSpriteShader;
    delete defaultQuadShader;
    delete camera;
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
  inline void deleteVector(std::vector<T*>* v) {
    for (int i = 0; i < v->size(); i++) {
      delete v->at(i);
      i--;
    }
    v->clear();
  }
};

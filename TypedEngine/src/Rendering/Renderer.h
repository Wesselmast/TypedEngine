#pragma once

#include "Sprite.h"
#include "Text.h"
#include "Quad.h"

#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "Core/Transform.h"

#include <vector>
#include <string>

class Renderer {
public:
  virtual void init(Camera* camera) = 0;
  virtual void setBlending(bool enabled) = 0;
  virtual void setCulling(bool enabled) = 0;

  virtual void drawSprite(Transform transform, Texture* texture) = 0;
  virtual void drawQuad(Transform transform, glm::vec4 color) = 0;
  virtual void drawText(Transform transform, std::string text) = 0;
  virtual void clear(glm::vec4 color) = 0;

  virtual void run() = 0;
  
  
  virtual ~Renderer() { 
    for(int i = 0; i < sprites.size(); i++) delete sprites[i];
    sprites.clear();
    for(int i = 0; i < texts.size(); i++) delete texts[i];
    texts.clear();
    for(int i = 0; i < quads.size(); i++) delete quads[i];
    quads.clear();
    
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
};

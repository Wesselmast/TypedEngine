#pragma once

#include "Sprite.h"

#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "Core/Transform.h"

#include <vector>

class Renderer {
public:
  virtual void init(Camera* camera) = 0;
  virtual void setBlending(bool enabled) = 0;

  virtual void drawSprite(Transform transform, Texture* texture) = 0;
  virtual void clear(glm::vec4 color) = 0;

  virtual void run() = 0;
  
  virtual ~Renderer() { 
    for(auto d : drawables) {
      delete d;
    }
    delete defaultTextShader;
    delete defaultSpriteShader;
    delete defaultQuadShader;
    delete camera;
  }

  std::vector<Sprite*> drawables;
protected:
  Shader* defaultTextShader;
  Shader* defaultSpriteShader;
  Shader* defaultQuadShader;
  Camera* camera;
};

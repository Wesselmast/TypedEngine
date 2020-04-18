#pragma once

#include "Renderer.h"
#include <algorithm>
#include "renderapi.h"



class RenderCommand {
public:
  inline static void init(Camera* camera) {
    renderer->init(camera);
  }
  
  inline static void setBlending(bool enabled) {
    renderer->setBlending(enabled);
  }
  
  inline static void clear(glm::vec4 backgroundColor) {
    renderer->clear(backgroundColor);
  }

  inline static void addSprite(Sprite*  sprite) {
    renderer->drawables.push_back(sprite);
  }

  inline static void removeSprite(Sprite*  sprite) {
    renderer->drawables.erase(std::remove(renderer->drawables.begin(), renderer->drawables.end(), sprite), renderer->drawables.end());
  }

  inline static void run() {
    renderer->run();
  }  
  
  inline static void end() {
    delete renderer;
  }
  
private:  
  static Renderer* renderer;
};

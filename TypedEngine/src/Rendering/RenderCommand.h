#pragma once

#include "Renderer.h"
#include <algorithm>

class RenderCommand {
public:
  inline static void init(Camera* camera) {
    renderer->init(camera);
  }
  
  inline static void setBlending(bool enabled) {
    renderer->setBlending(enabled);
  }

  inline static void setCulling(bool enabled) {
    renderer->setCulling(enabled);
  }
  
  inline static void clear(glm::vec4 backgroundColor) {
    renderer->clear(backgroundColor);
  }
  
  inline static void addSprite(Sprite* sprite) {
    if (!renderer) return;
    renderer->sprites.push_back(sprite);
  }
  
  inline static void removeSprite(Sprite* sprite) {
    if (!renderer) return;
    auto it = std::find(renderer->sprites.begin(), renderer->sprites.end(), sprite);
    if (it != renderer->sprites.end()) {
       renderer->sprites.erase(it);
    }
  }
  
  inline static void addText(Text* text) {
    if (!renderer) return; 
    renderer->texts.push_back(text);
  }
  
  inline static void removeText(Text* text) {
    if (!renderer) return;
    auto it = std::find(renderer->texts.begin(), renderer->texts.end(), text);
    if (it != renderer->texts.end()) {
       renderer->texts.erase(it);
    }
  }
  
  inline static void addQuad(Quad* quad) {
    if (!renderer) return;    
    renderer->quads.push_back(quad);
  }
  
  inline static void removeQuad(Quad* quad) {
    if (!renderer) return;
    auto it = std::find(renderer->quads.begin(), renderer->quads.end(), quad);
    if (it != renderer->quads.end()) {
       renderer->quads.erase(it);
    }
  }
  
  inline static void removeTagged(Tag tag) {
    renderer->deleteVectorByTag<Sprite>(&(renderer->sprites), tag);
    renderer->deleteVectorByTag<Text>(&(renderer->texts), tag);
    renderer->deleteVectorByTag<Quad>(&(renderer->quads), tag);
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

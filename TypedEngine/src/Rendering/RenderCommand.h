#pragma once

#include "Renderer.h"
#include <algorithm>
#include <stdio.h>

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
  
  inline static void getTagged(Tag tag, std::vector<Entity*>* v) {
    std::vector<Sprite*> a = renderer->getVectorByTag<Sprite>(&(renderer->sprites), tag);
    std::vector<Text*> b = renderer->getVectorByTag<Text>(&(renderer->texts), tag);
    std::vector<Quad*> c = renderer->getVectorByTag<Quad>(&(renderer->quads), tag);
    v->insert(v->end(), a.begin(), a.end());
    v->insert(v->end(), b.begin(), b.end());
    v->insert(v->end(), c.begin(), c.end());    
    std::sort(v->begin(), v->end(), [](Entity* e1, Entity* e2) -> bool {
       return e1->transform.zOffset > e2->transform.zOffset;
    });
  }

  inline static void print() {
    printf("Renderer: \n");
    printf("   Sprites: %d\n", renderer->sprites.size());
    for(auto e : renderer->sprites) {
      printf("      %s: size: %d, tag: %d, tex: %s, zoff: %d\n", e->name.c_str(), sizeof(e), e->tag, e->textureName, e->transform.zOffset);
    }
    printf("   Quads: %d\n", renderer->quads.size());
    for(auto e : renderer->quads) {
      printf("      %s: size: %d, tag: %d, zoff: %d\n", e->name.c_str(), sizeof(e), e->tag, e->transform.zOffset);
    }
    printf("   Texts: %d\n", renderer->texts.size());
    for(auto e : renderer->texts) {
      printf("      %s: size: %d, tag: %d, zoff: %d\n", e->name.c_str(), sizeof(e), e->tag, e->transform.zOffset);
    }
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

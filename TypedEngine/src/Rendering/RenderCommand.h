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
    renderer->sprites.erase(std::remove(renderer->sprites.begin(), renderer->sprites.end(), sprite), renderer->sprites.end());
  }
  
  inline static void addText(Text* text) {
	  if (!renderer) return; 
	  renderer->texts.push_back(text);
  }
  
  inline static void removeText(Text* text) {
	  if (!renderer) return;
	  renderer->texts.erase(std::remove(renderer->texts.begin(), renderer->texts.end(), text), renderer->texts.end());
  }

  inline static void addQuad(Quad* quad) {
	  if (!renderer) return;
	  renderer->quads.push_back(quad);
  }

  inline static void removeQuad(Quad* quad) {
	  if (!renderer) return;
	  renderer->quads.erase(std::remove(renderer->quads.begin(), renderer->quads.end(), quad), renderer->quads.end());
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

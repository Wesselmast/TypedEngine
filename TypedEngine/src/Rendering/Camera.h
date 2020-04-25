#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Window/Window.h"
#include "Core/Transform.h"

class Camera {
public:
  Camera() {
  }
  
  Camera(Window* window) : window(window) {
  }

  //@CleanUp: This is so ugly... fix this up later!
  inline void setTransform(Transform transform) { this->transform = transform; }
  inline void setPosition(glm::vec2 position) { this->transform.position = position; }
  inline void setScale(glm::vec2 scale) { this->transform.scale = scale; }
  inline void setRotation(float rotation) { this->transform.rotation = rotation; }
  
  inline Transform getTransform() { return transform; }
  inline glm::vec2 getPosition() { return transform.position; }
  inline glm::vec2 getScale () { return transform.scale; }
  inline float getRotation() { return transform.rotation; }

  inline glm::mat4 getProjection() { return projection; }

  void updateProjection();
  glm::mat4 getViewProjection();

  Transform transform;
private:
  glm::mat4 projection;
  Window* window;
};

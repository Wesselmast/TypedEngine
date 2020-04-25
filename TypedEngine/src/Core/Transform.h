#pragma once

#include "glm/glm.hpp"

struct Transform {
   Transform() : position(glm::vec2(0.0f, 0.0f)), rotation(0.0f), scale(glm::vec2(1.0f, 1.0f)) {
   }
  
   Transform(glm::vec2 position, float rotation, glm::vec2 scale) : position(position), rotation(rotation), scale(scale) { 
   }
  
  glm::vec2 position;
  float rotation;
  glm::vec2 scale;
};

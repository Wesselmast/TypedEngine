#pragma once

#include "glm/glm.hpp"

struct Camera;
struct Window;

glm::vec2 worldToScreen(Camera* camera, Window* window, glm::vec2 point);
glm::vec2 screenToWorld(Camera* camera, Window* window, glm::vec2 point);

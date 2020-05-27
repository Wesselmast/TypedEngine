#include "Math.h"

#include "Rendering/Camera.h"
#include "Window/Window.h"

glm::vec2 worldToScreen(Camera* camera, Window* window, glm::vec2 point) {
  double x = 2.0 * (point.x / window->getSize().x) - 1.0;
  double y = 2.0 * (point.y / window->getSize().y) - 1.0;

  glm::vec4 sp(x, -y, -1.0f, 1.0f);
  glm::vec3 screenPos(camera->getViewProjection() * sp);

  screenPos.x += 1.0f;
  screenPos.x *= 0.5f * window->getSize().x;
  screenPos.y += 1.0f;
  screenPos.y *= 0.5f * window->getSize().y;

  return glm::vec2(screenPos.x, screenPos.y);
}

glm::vec2 screenToWorld(Camera* camera, Window* window, glm::vec2 point) {
  double x = 2.0 * (point.x / window->getSize().x) - 1.0;
  double y = 2.0 * (point.y / window->getSize().y) - 1.0;

  glm::vec4 screenPos = glm::vec4(x, -y, -1.0f, 1.0f);

  return glm::vec3(glm::inverse(camera->getViewProjection()) * screenPos);
}

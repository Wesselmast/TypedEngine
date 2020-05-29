#pragma once

#include "glm/glm.hpp"
#include "glm/glm.hpp"

glm::vec4 hexToColor(char* hex);
char* colorToHex(const glm::vec4& color);

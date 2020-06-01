#pragma once

#include "glm/glm.hpp"

glm::vec4 hexToColor(const char* hex);
const char* colorToHex(const glm::vec4& color);
float stringToFloat(const char* str);

#include "Utility.h"

#include <stdio.h>
#include <sstream>
#include <cstring>

glm::vec4 hexToColor(const char* hex) {
  glm::vec4 vec;
  std::stringstream stream;
  unsigned int hexValue;
  stream << std::hex << hex;
  stream >> hexValue;
  vec.x = ((hexValue >> 24) & 0xFF) / 255.0f;
  vec.y = ((hexValue >> 16) & 0xFF) / 255.0f;
  vec.z = ((hexValue >>  8) & 0xFF) / 255.0f;
  vec.w = ((hexValue >>  0) & 0xFF) / 255.0f;
  return vec;
}

const char* colorToHex(const glm::vec4& color) {
  std::stringstream stream;
  stream << "#";  
  stream << std::hex << ((int)(color.x * 255.0f) << 24 |
			 (int)(color.y * 255.0f) << 16 |
			 (int)(color.z * 255.0f) <<  8 |
			 (int)(color.w * 255.0f) <<  0);  
  const std::string tmp = stream.str();
  char* tmp2 = new char[strlen(tmp.c_str()) + 1];
  memcpy(tmp2, tmp.c_str(), strlen(tmp.c_str()) + 1);
  return tmp2;
}

float stringToFloat(const char* str) {
  char* endptr;
  float result = strtol(str, &endptr, 10);
  if (*endptr) {
    printf("Input %s is not a number!", str);
    return 0;
  }
  return result;
}

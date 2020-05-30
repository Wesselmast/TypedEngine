#include "Utility.h"

#include <sstream>

glm::vec4 hexToColor(const char* hex) {
  glm::vec4 vec;
  std::stringstream stream;
  stream << std::hex << hex[0];
  stream << std::hex << hex[1];
  stream >> vec.x;
  stream << std::hex << hex[2];
  stream << std::hex << hex[3];
  stream >> vec.y;
  stream << std::hex << hex[4];
  stream << std::hex << hex[5];
  stream >> vec.z;
  stream << std::hex << hex[6];
  stream << std::hex << hex[7];
  stream >> vec.w;
  return vec;
}

const char* colorToHex(const glm::vec4& color) {
  std::stringstream stream;
  stream << std::hex << color.x;  
  stream << std::hex << color.y;  
  stream << std::hex << color.z;  
  stream << std::hex << color.w;
  return stream.str().c_str();
}

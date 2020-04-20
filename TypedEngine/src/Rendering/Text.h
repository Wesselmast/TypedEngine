#pragma once

#include "core/entity.h"
#include <string>

class Text : public Entity {
 public:
  Text();
  ~Text();
  Text(Transform transform);
  Text(const std::string& text);
  Text(Transform transform, const std::string& text);
public:
  std::string text;
private:
  void init(Transform transform, const std::string& text);
};

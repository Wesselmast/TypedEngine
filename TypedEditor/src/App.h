#pragma once

#include "Application.h"
#include <memory>
#include <vector>

class Sprite;

class App : public Application {
  
public:
  void begin() override;
  void tick(float deltaTime, float time) override;
  
  void onKeyPressed(Key key, Modifier mod) override;
  void onKeyReleased(Key key, Modifier mod) override;
  void onMouseScrolled(float offsetX, float offsetY) override;
  void onWindowRefreshed() override;
  void onMousePressed(MouseButton button) override;
  
private:
  Sprite* treeSprite;
};

#pragma once

#include "Application.h"
#include <memory>

struct Camera;
struct Sprite;

class App : public Application {

public:
	void begin() override;
	void tick(float deltaTime, float time) override;

	void onKeyPressed(Key key, Modifier mod) override;
	void onKeyReleased(Key key, Modifier mod) override;
	void onMouseScrolled(float offsetX, float offsetY) override;
	
private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Sprite> sprite;
};


#pragma once

#include "../src/Application.h"
#include <memory>

struct Camera;
struct Texture;

class App : public Application {

public:
	void begin() override;
	void tick(float deltaTime) override;

	void onKeyPressed(Key key, Modifier mod) override;
	void onKeyReleased(Key key, Modifier mod) override;
	void onMouseScrolled(float offsetX, float offsetY) override;
	void onWindowRefreshed() override;
	
private:
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Texture> texture;
};
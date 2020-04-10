#pragma once

#include "Window/Window.h"
#include "glm/glm.hpp"

enum class Key {
	THING = 1
};

enum class Button {
	THING = 1
};

enum class Modifier {
	THING = 1
};

class Application {
public:
	virtual void begin() {}
	virtual void tick(float deltaTime) {}
	virtual void end() {}

	virtual void onWindowResized(int width, int height) {}
	virtual void onWindowRefreshed() {}
	virtual void onWindowMoved(int posX, int posY) {}
	
	virtual void onMousePressed(Button button) {}
	virtual void onMouseReleased(Button button) {}
	virtual void onMouseMoved(int posX, int posY) {}
	virtual void onMouseScrolled(float offsetX, float offsetY) {}

	virtual void onKeyPressed(Key key, Modifier mod) {}
	virtual void onKeyReleased(Key key, Modifier mod) {}

	Window* window;
	static Application* application;
};


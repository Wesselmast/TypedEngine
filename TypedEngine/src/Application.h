#pragma once

#include "Window/Window.h"
#include "Input/Input.h"

#include "glm/glm.hpp"

class Application {
public:
	virtual void begin() {}
	virtual void tick(float deltaTime) {}
	virtual void end() {}

	virtual void onWindowResized(int width, int height) {}
	virtual void onWindowMoved(int posX, int posY) {}
	
	virtual void onMousePressed(MouseButton button) {}
	virtual void onMouseReleased(MouseButton button) {}
	virtual void onMouseMoved(int posX, int posY) {}
	virtual void onMouseScrolled(float offsetX, float offsetY) {}

	virtual void onKeyPressed(Key key, Modifier mod) {}
	virtual void onKeyReleased(Key key, Modifier mod) {}

	Window* window;
	static Application* application;
};


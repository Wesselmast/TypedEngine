#pragma once
#include "glm/glm.hpp"

class Window {
public:
	virtual ~Window() = default;

	virtual void setVSync(bool enabled) = 0;
	virtual void refreshViewport() = 0;
	virtual bool isRunning() const = 0;
	virtual void swapBuffers() = 0;
	virtual glm::vec2 getSize() const = 0;
};
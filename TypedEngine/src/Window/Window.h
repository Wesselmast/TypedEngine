#pragma once
#include "glm/glm.hpp"

enum class Key;
enum class Modifier;

typedef void(*fptr_NoParams)();

typedef void(*fptr_MouseScrolled)(float, float);
typedef void(*fptr_KeyAction)(Key, Modifier);

class Window {
public:
	virtual ~Window() = default;

	virtual void setVSync(bool enabled) = 0;
	virtual void refreshViewport() = 0;
	virtual bool isRunning() const = 0;
	virtual void swapBuffers() = 0;
	virtual glm::vec2 getSize() const = 0;
	virtual void close() = 0;

	void callback_mouseScrolled(fptr_MouseScrolled function) { mouseScrolledFunction = function; }
	void callback_keyPressed(fptr_KeyAction function) { keyPressedFunction = function; }
	void callback_keyReleased(fptr_KeyAction function) { keyReleasedFunction = function; }
	void callback_windowRefreshed(fptr_NoParams function) { windowRefreshFunction = function; }

protected:
	static fptr_MouseScrolled mouseScrolledFunction;
	static fptr_KeyAction keyPressedFunction;
	static fptr_KeyAction keyReleasedFunction;
	static fptr_NoParams windowRefreshFunction;
};
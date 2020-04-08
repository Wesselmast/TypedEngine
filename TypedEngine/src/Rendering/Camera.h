#pragma once
//#include "glfw/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Core/Transform.h"

struct GLFWwindow;

class Camera {
public:
		// @CleanUp: Take in my own window class instead
	Camera(GLFWwindow* window) {
		this->window = window;
	}

	inline void setTransform(Transform transform) { this->transform = transform; }
	inline void setPosition(glm::vec2 position) { this->transform.position = position; }
	inline void setScale(glm::vec2 scale) { this->transform.scale = scale; }
	inline void setRotation(float rotation) { this->transform.rotation = rotation; }

	inline Transform getTransform() { return transform; }
	inline glm::vec2 getPosition() { return transform.position; }
	inline glm::vec2 getScale () { return transform.scale; }
	inline float getRotation() { return transform.rotation; }

	glm::mat4 getViewProjection();
private:
	GLFWwindow* window;
	Transform transform;
};
#pragma once

#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "glm/glm.hpp"

struct Transform {
	Transform() {
	}

	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : position(position), rotation(rotation), scale(scale) {
	}

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

class Renderer {
public:
	virtual void init() = 0;
	virtual void setBlending(bool enabled) = 0;
	virtual void clear(glm::vec4 backgroundColor) = 0;
	virtual void drawSprite(Texture* texture, Shader* shader, Transform transform, glm::mat4 viewProjection, VertexArray* vertexArray) = 0;
};
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
	virtual void drawSprite(Transform transform, glm::mat4 viewProjection, VertexArray* vertexArray) = 0;
	virtual void drawSprite(Transform transform, glm::mat4 viewProjection, VertexArray* vertexArray, Texture* texture) = 0;

	virtual ~Renderer() { 
		delete defaultShader;
		delete defaultTexture;
	}
protected:
	inline void setDefaultShader(Shader* shader) {
		defaultShader = shader;
	}

	inline void setDefaultTexture(Texture* texture) {
		defaultTexture = texture;
	}

	inline Shader* getDefaultShader() const {
		return defaultShader;
	}

	inline Texture* getDefaultTexture() const {
		return defaultTexture;
	}

private:
	Shader* defaultShader;
	Texture* defaultTexture;
};
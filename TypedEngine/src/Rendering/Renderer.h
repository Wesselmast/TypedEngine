#pragma once

#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "../Core/Transform.h"

class Renderer {
public:
	virtual void init(Camera* camera) = 0;
	virtual void setBlending(bool enabled) = 0;
	virtual void clear(glm::vec4 backgroundColor) = 0;
	virtual void drawSprite(Transform transform) = 0;
	virtual void drawSprite(Transform transform, Texture* texture) = 0;

	virtual ~Renderer() { 
		delete defaultShader;
		delete defaultTexture;
		delete camera;
	}
protected:
	inline void setDefaultShader(Shader* shader) { defaultShader = shader; }
	inline void setDefaultTexture(Texture* texture) { defaultTexture = texture; }
	inline void setCamera(Camera* camera) { this->camera = camera; }

	inline Shader* getDefaultShader() const { return defaultShader; }
	inline Texture* getDefaultTexture() const { return defaultTexture; }
	inline Camera* getCamera() const { return camera; }
private:
	Shader* defaultShader;
	Texture* defaultTexture;
	Camera* camera;
};
#pragma once
#include "../Renderer.h"

class OpenGLRenderer : public Renderer {
	virtual void init(Camera* camera) override;
	virtual void setBlending(bool enabled) override;

	virtual void clear(glm::vec4 color) override;
	virtual void drawSprite(Transform transform, VertexArray * vertexArray) override;
	virtual void drawSprite(Transform transform, VertexArray * vertexArray, Texture * texture) override;
};
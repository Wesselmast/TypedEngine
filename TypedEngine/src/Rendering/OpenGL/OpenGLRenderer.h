#pragma once
#include "../Renderer.h"

class OpenGLRenderer : public Renderer {
	virtual void init() override;
	virtual void setBlending(bool enabled) override;

	virtual void clear(glm::vec4 color) override;
	virtual void drawSprite(Texture * texture, Shader * shader, Transform transform, glm::mat4 viewProjection, VertexArray * vertexArray) override;
};
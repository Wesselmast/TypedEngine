#pragma once

#include "Renderer.h"

static class RenderCommand {
public:
	inline static void init() {
		renderer->init();
	}

	inline static void setBlending(bool enabled) {
		renderer->setBlending(enabled);
	}

	inline static void clear(glm::vec4 backgroundColor) {
		renderer->clear(backgroundColor);
	}

	inline static void drawSprite(Texture* texture, Shader* shader, Transform transform, glm::mat4 viewProjection, VertexArray* vertexArray) {
		renderer->drawSprite(texture, shader, transform, viewProjection, vertexArray);
	}

private:
	~RenderCommand() {
		delete renderer;
	}

	static Renderer* renderer;
};
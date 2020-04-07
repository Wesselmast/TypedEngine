#pragma once

#include "Renderer.h"

class RenderCommand {
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

	inline static void drawSprite(Transform transform, glm::mat4 viewProjection, VertexArray* vertexArray) {
		renderer->drawSprite(transform, viewProjection, vertexArray);
	}

	inline static void drawSprite(Transform transform, glm::mat4 viewProjection, VertexArray* vertexArray, Texture* texture) {
		renderer->drawSprite(transform, viewProjection, vertexArray, texture);
	}

private:
	~RenderCommand() {
		delete renderer;
	}

	static Renderer* renderer;
};
#pragma once

#include "Renderer.h"

class RenderCommand {
public:
	inline static void init(Camera* camera) {
		renderer->init(camera);
	}

	inline static void setBlending(bool enabled) {
		renderer->setBlending(enabled);
	}

	inline static void clear(glm::vec4 backgroundColor) {
		renderer->clear(backgroundColor);
	}

	inline static void drawSprite(Transform transform) {
		renderer->drawSprite(transform);
	}

	inline static void drawSprite(Transform transform, Texture* texture) {
		renderer->drawSprite(transform, texture);
	}

private:
	~RenderCommand() {
		delete renderer;
	}

	static Renderer* renderer;
};
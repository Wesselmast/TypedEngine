#include "App.h"

/* @CleanUp: Fix these include paths, they are hidious */
#include "../src/Core/Transform.h"

#include "../src/Window/OpenGL/OpenGLWindow.h"

#include "../src/Rendering/OpenGL/OpenGLTexture.h"
#include "../src/Rendering/RenderCommand.h"
#include "../src/Rendering/Camera.h"

#include <iostream>

glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

glm::vec2 position = glm::vec3(0, 0, 0);
float rotation = 0.0f;

const float rotSpeed = 3.0f;
const float panSpeed = 750.0f;

void App::begin() {
	camera = std::make_shared<Camera>(window);
	RenderCommand::init(camera.get()); // @Security: Add an error message telling people they shouldn't do anything render-related before this

	texture = std::make_shared<OpenGLTexture>("res/textures/T_Tree.png");
}

void App::tick(float deltaTime) {
	position += input * deltaTime * zoom * panSpeed;
	camera->setPosition(position);
	camera->setScale(glm::vec2(zoom));


	//ToDo @Optimization: check if transforms are in camera viewport (if not, cull them)
	for (int i = 0; i < 2; i++)
	{
		Transform transform = { { 1024.0f * i, 0.0f }, 0.0f, { 1.0f, 1.0f} };

		//ToDo @CleanUp: get to a point where I just have to 'create' a sprite at some point and have the back-end push it onto a runtime loop (hide rendering)
		RenderCommand::drawSprite(transform);
	}

	{
		Transform transform = { { 1000, 1250.0f }, 0.0f, { 1.0f, 1.0f } };
		RenderCommand::drawSprite(transform, texture.get());
	}
}

void App::onKeyPressed(Key key, Modifier mod) {

}

void App::onKeyReleased(Key key, Modifier mod) {
	window->close();
}

void App::onMouseScrolled(float offsetX, float offsetY) {
	zoom += -offsetY * 0.5f;
	if (zoom <= 0.01f) {
		zoom = 0.1f;
	}
	else if (zoom >= 10) {
		zoom = 10;
	}
}

void App::onWindowRefreshed() {
	window->refreshViewport();
}

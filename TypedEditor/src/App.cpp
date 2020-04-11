#include "App.h"

/* @CleanUp: Fix these include paths, they are hidious */
#include "Core/Transform.h"

#include "Window/OpenGL/OpenGLWindow.h"

#include "Rendering/OpenGL/OpenGLTexture.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Camera.h"

#include <iostream>

extern "C" {
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

glm::vec2 position = glm::vec3(0, 0, 0);
const float zoomSpeed = 0.5f;
const float panSpeed = 750.0f;



// ToDo: @CleanUp: Move rendercommands to main file (main should handle all rendering, this should handle other stuff)
void App::begin() {
	camera = std::make_shared<Camera>(window);
	RenderCommand::init(camera.get()); // @Security: Add an error message telling people they shouldn't do anything render-related before this

	texture = std::make_shared<OpenGLTexture>("res/textures/T_Tree.png");




	lua_State* L = luaL_newstate();
	const char* command = "r = 500 * 2";

	luaL_dostring(L, command);
	lua_getglobal(L, "r");
	std::cout << "500 * 2 = " << (int)lua_tonumber(L, 1) << std::endl;





	lua_close(L);



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
	switch (key) {
		case Key::W: input.y =  1.0f; break;
		case Key::A: input.x = -1.0f; break;
		case Key::S: input.y = -1.0f; break;
		case Key::D: input.x =  1.0f; break;
		case Key::ESCAPE: window->close(); break;
	}
}

void App::onKeyReleased(Key key, Modifier mod) {
	switch (key) {
		case Key::W: input.y =  0.0f; break;
		case Key::A: input.x = -0.0f; break;
		case Key::S: input.y = -0.0f; break;
		case Key::D: input.x =  0.0f; break;
	}
}

void App::onMouseScrolled(float offsetX, float offsetY) {
	zoom += -offsetY * zoomSpeed;
	if (zoom <= 0.01f) {
		zoom = 0.1f;
	}
	else if (zoom >= 10) {
		zoom = 10;
	}
}

Application* createApplication() {
	return new App();
}
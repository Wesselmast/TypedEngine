#include <GLFW/glfw3.h>

#include "Core/Transform.h"

#include "Window/OpenGL/OpenGLWindow.h"

#include "Rendering/OpenGL/OpenGLTexture.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Camera.h"

#include "glm/glm.hpp"

#include <iostream>

glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

/* INPUT POLLING STUFF */
static void recieveInput(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
		return;
	}
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_W: input.y   =  1.0f; break;
			case GLFW_KEY_S: input.y   = -1.0f; break;
			case GLFW_KEY_A: input.x   = -1.0f; break;
			case GLFW_KEY_D: input.x   =  1.0f; break;
			default: input = glm::vec2(0, 0);
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_W: input.y   =  0.0f; break;
			case GLFW_KEY_S: input.y   =  0.0f; break;
			case GLFW_KEY_A: input.x   =  0.0f; break;
			case GLFW_KEY_D: input.x   =  0.0f; break;
		}
	}
}

static void scrollInput(GLFWwindow* window, double xoffset, double yoffset) {
	zoom += -yoffset * 0.5f; // x = zoomspeed
	if (zoom <= 0.01f) {
		zoom = 0.1f;
	}
	else if (zoom >= 10) {
		zoom = 10;
	}
}

int main() {
	Window* window = new OpenGLWindow({ 1920, 1080 }, "TypedEngine", false);

	//glfwSetKeyCallback(window, recieveInput);
	//glfwSetScrollCallback(window, scrollInput);
	
	Camera* camera = new Camera(window);

	RenderCommand::init(camera); // @Security: Add an error message telling people they shouldn't do anything render-related before this
	Texture* texture = new OpenGLTexture("res/textures/T_Tree.png");

	/* @CleanUp: this is just random crap */

	float previous = (float)glfwGetTime();
	glm::vec2 position = glm::vec3(0, 0, 0);
	float rotation = 0.0f;
	glm::vec4 objectColor(142 / 255.0f, 104 / 255.0f, 70 / 255.0f, 1.0f); //@Unused: Unused variable but nice color :)
	glm::vec4 clearColor(233/255.0f, 233 / 255.0f, 245 / 255.0f, 1.0f);
	const float rotSpeed = 3.0f;
	const float panSpeed = 750.0f;

	/* RENDERING */
	while (window->isRunning()) {
		/* DELTATIME STUFF */
		float time = (float)glfwGetTime();
		float deltaTime = time - previous;
		std::cout << 1/deltaTime << std::endl;

		RenderCommand::clear(clearColor);
		window->refreshViewport();

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
			RenderCommand::drawSprite(transform, texture);
		}

		window->swapBuffers();
		glfwPollEvents();


		/*    WE NEVER UNBIND ANYTHING. THIS MIGHT CAUSE PROBLEMS AT SOME POINT    */

		//
		previous = time;
	}

	delete texture;
	delete camera;
	return 0;
}
#include "glfw/glfw3.h"

#include "Application.h"

#include "Window/OpenGL/OpenGLWindow.h"
#include "Rendering/RenderCommand.h"

#include "glm/glm.hpp"

Application* app;

static void callback_keyPressed(Key key, Modifier mod) { app->onKeyPressed(key, mod); }
static void callback_keyReleased(Key key, Modifier mod) { app->onKeyReleased (key, mod); }
static void callback_mouseScrolled(float offsetx, float offsety) { app->onMouseScrolled(offsetx, offsety); }

int main() {
	app = createApplication();

	Window* window = new OpenGLWindow({ 680, 480 }, "TypedEngine", false);

	window->callback_keyPressed(callback_keyPressed);
	window->callback_keyReleased(callback_keyReleased);
	window->callback_mouseScrolled(callback_mouseScrolled);

	app->window = window;

	app->begin();

	float previous = (float)glfwGetTime();

	while (window->isRunning()) {
		float time = (float)glfwGetTime();
		float deltaTime = time - previous;

		RenderCommand::clear(glm::vec4(233 / 255.0f, 233 / 255.0f, 245 / 255.0f, 1.0f));

		app->tick(deltaTime);
		
		
		window->swapBuffers();

		previous = time;
	}

	delete app;
	return 0;
}
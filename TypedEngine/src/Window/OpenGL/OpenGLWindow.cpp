#include "OpenGLWindow.h"

#include <GLFW/glfw3.h>

OpenGLWindow::OpenGLWindow(glm::vec2 size, const char * name, bool fullscreen) {

	if (!glfwInit()) {
		// ERROR MESSAGE
		return;
	}

	GLFWmonitor* monitor = fullscreen ? glfwGetPrimaryMonitor() : NULL;

	window = glfwCreateWindow((int)size.x, (int)size.y, name, monitor, NULL);
	if (!window) {
		glfwTerminate();
		// ERROR MESSAGE
		return;
	}

	glfwMakeContextCurrent(window);
	/*glfwSetKeyCallback(window, recieveInput);
	glfwSetScrollCallback(window, scrollInput);*/

	setVSync(true);
}

OpenGLWindow::~OpenGLWindow() {
	glfwTerminate();
}

glm::vec2 OpenGLWindow::getSize() const {
	int width;
	int height;
	glfwGetFramebufferSize(window, &width, &height);
	
	return { (float)width, (float)height };
}

void OpenGLWindow::setVSync(bool enabled) {
	glfwSwapInterval(enabled);
}

void OpenGLWindow::refreshViewport() {
	glm::vec2 size = getSize();
	glViewport(0, 0, size.x, size.y);
}

bool OpenGLWindow::isRunning() const {
	return !glfwWindowShouldClose(window);
}

void OpenGLWindow::swapBuffers() {
	glfwSwapBuffers(window);
}

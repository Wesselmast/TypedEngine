#include "Camera.h"

glm::mat4 Camera::getViewProjection() {

	// ToDo: @CleanUp: Replace this with window->getSize()
	int width = 1920;
	int height = 1080;
	//glfwGetFramebufferSize(window, &width, &height);
	
	// ToDo @CleanUp: Recalculating projection should just happen on a window resize event
	glm::mat4 projection = glm::ortho(-(float)width, (float)width, -(float)height, (float)height, -1.0f, 1.0f);

	glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position, 0.0f));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), transform.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(transform.scale, 1.0f));
	glm::mat4 transformMatrix = positionMatrix * rotationMatrix * scaleMatrix;
	glm::mat4 view = glm::inverse(transformMatrix);

	return projection * view;
}
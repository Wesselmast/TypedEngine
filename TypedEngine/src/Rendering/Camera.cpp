#include "Camera.h"

#include <glm/gtx/rotate_vector.hpp>

glm::mat4 Camera::getViewProjection() {
	float w = window->getSize().x;
	float h = window->getSize().y;

	// ToDo @CleanUp: Recalculating projection should just happen on a window resize event
	glm::mat4 projection = glm::ortho(-w, w, -h, h, -1.0f, 1.0f);

	glm::mat4 positionMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(glm::rotate(transform.position, transform.rotation), 0.0f));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), transform.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(transform.scale, 1.0f));
	glm::mat4 transformMatrix = positionMatrix * rotationMatrix * scaleMatrix;
	glm::mat4 view = glm::inverse(transformMatrix);

	return projection * view;
}

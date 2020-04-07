#include "OpenGLRenderer.h"

#include <GL/glew.h>
#include "glm/gtx/quaternion.hpp"

//IMPORTANT @CleanUp: Make own error logging function and include that instead;
#include <stdio.h>


void OpenGLRenderer::init() {
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "ERROR: Glew could not be initialized!!");
		return;
	}
	setBlending(true);
}

void OpenGLRenderer::setBlending(bool enabled) {
	if (enabled) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDisable(GL_BLEND);
	}
}

void OpenGLRenderer::clear(glm::vec4 color) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(color.x, color.y, color.z, color.w);
}

void OpenGLRenderer::drawSprite(Texture * texture, Shader * shader, Transform transform, glm::mat4 viewProjection, VertexArray * vertexArray) {
	glm::mat4 position = glm::translate(glm::mat4(1.0f), transform.position);
	glm::mat4 rotation = glm::toMat4(glm::quat(transform.rotation));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), transform.scale);

	glm::mat4 model = position * rotation * scale;
	glm::mat4 mvp = viewProjection * model;

	shader->bind();
	texture->bind();
	shader->setUniformMat4("uMvpMatrix", mvp);
	shader->setUniformInt1("uTexture", 0);

	vertexArray->bind();
	glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
}



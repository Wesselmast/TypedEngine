#include "OpenGLRenderer.h"

#include <GL/glew.h>
#include "glm/gtx/quaternion.hpp"

//IMPORTANT @CleanUp: Make own error logging function and include that instead;
#include <stdio.h>

#include "OpenGLShader.h"
#include "OpenGLTexture.h"


void OpenGLRenderer::init(Camera* camera) {
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "ERROR: Glew could not be initialized!!");
		return;
	}

	setBlending(true);

	setCamera(camera);
	setDefaultShader(new OpenGLShader("res/shaders/default.shader"));
	setDefaultTexture(new OpenGLTexture("res/textures/T_Default.jpg"));
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
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::drawSprite(Transform transform, VertexArray * vertexArray) {
	drawSprite(transform, vertexArray, getDefaultTexture());
}

void OpenGLRenderer::drawSprite(Transform transform, VertexArray * vertexArray, Texture * texture) {
	glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position, 0.0f));
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), transform.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(transform.scale, 1.0f));

	glm::mat4 model = position * rotation * scale;
	glm::mat4 mvp = getCamera()->getViewProjection() * model;

	texture->bind();
	vertexArray->bind();

	getDefaultShader()->bind();
	getDefaultShader()->setUniformMat4("uMvpMatrix", mvp);
	getDefaultShader()->setUniformInt1("uTexture", 0);

	glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
}


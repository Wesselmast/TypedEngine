#include "OpenGLVertexArray.h"

#include "glad/glad.h"

OpenGLVertexArray::OpenGLVertexArray() {
	glGenVertexArrays(1, &rendererID);
	glBindVertexArray(rendererID);
}

OpenGLVertexArray::~OpenGLVertexArray() {
	glDeleteVertexArrays(1, &rendererID);
}

void OpenGLVertexArray::setVertexBuffer(VertexBuffer * vertexBuffer) {
	glBindVertexArray(rendererID);

	this->vertexBuffer = vertexBuffer;
	vertexBuffer->bind();
	
	unsigned int* layout = vertexBuffer->getLayout();
	unsigned int  layoutSize = vertexBuffer->getLayoutSize();

	unsigned int stride = 0;
	for (unsigned int i = 0; i < layoutSize; i++) {
		stride += layout[i] * sizeof(float);
	}

	size_t offset = 0;
	for (unsigned int i = 0; i < layoutSize; i++) {
		glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(i);
		offset += layout[i] * sizeof(float);
	}
}

void OpenGLVertexArray::setIndexBuffer(IndexBuffer * indexBuffer) {
	glBindVertexArray(rendererID);

	this->indexBuffer = indexBuffer;
	indexBuffer->bind();
}

void OpenGLVertexArray::bind() {
	glBindVertexArray(rendererID);
}

void OpenGLVertexArray::unbind() {
	glBindVertexArray(0);
}
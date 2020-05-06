#include "PCH.h"

#include "OpenGLVertexBuffer.h"

#include "glad/glad.h"

OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, unsigned int size) {
  glGenBuffers(1, &rendererID);
  glBindBuffer(GL_ARRAY_BUFFER, rendererID);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void OpenGLVertexBuffer::addSubData(float* vertices, unsigned int size) {
  glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices); 
}

OpenGLVertexBuffer::~OpenGLVertexBuffer() {
  glDeleteBuffers(1, &rendererID);
}

void OpenGLVertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void OpenGLVertexBuffer::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#include "OpenGLShader.h"

#include "glad/glad.h"

#include <iostream>

OpenGLShader::OpenGLShader(const char * path) {
  parseShader(path, &source);
  
  rendererID = glCreateProgram();
  GLuint v = createShader(ShaderType::VERTEX);
  GLuint f = createShader(ShaderType::FRAGMENT);
  glAttachShader(rendererID, v);
  glAttachShader(rendererID, f);
  glLinkProgram(rendererID);
  glValidateProgram(rendererID);
  
  glDetachShader(rendererID, v);
  glDetachShader(rendererID, f);
}

OpenGLShader::~OpenGLShader() {
  glDeleteProgram(rendererID);
}

void OpenGLShader::bind() {
  glUseProgram(rendererID);
}

void OpenGLShader::unbind() {
  glUseProgram(0);
}

void OpenGLShader::setUniformFloat4(const char * name, glm::vec4 value) {
  glUniform4f(glGetUniformLocation(rendererID, name), value.x, value.y, value.z, value.w);
}

void OpenGLShader::setUniformFloat2(const char * name, glm::vec2 value) {
  glUniform2f(glGetUniformLocation(rendererID, name), value.x, value.y);
}

void OpenGLShader::setUniformMat4(const char * name, glm::mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(rendererID, name), 1, GL_FALSE, &value[0][0]);
}

void OpenGLShader::setUniformInt1(const char * name, int value) {
  glUniform1i(glGetUniformLocation(rendererID, name), value);
}

unsigned int OpenGLShader::createShader(ShaderType type) {
  GLenum enumType;
  const char* sourceType;
  
  switch (type) {
  case ShaderType::VERTEX: {
    enumType = GL_VERTEX_SHADER;
    sourceType = source.vertex;
    break;
  }
  case ShaderType::FRAGMENT: {
    enumType = GL_FRAGMENT_SHADER;
    sourceType = source.fragment;
    break;
  }
  }
  
  GLuint result = glCreateShader(enumType);
  glShaderSource(result, 1, &sourceType, NULL);
  glCompileShader(result);
  
  GLint iv;
  glGetShaderiv(result, GL_COMPILE_STATUS, &iv);
  if (iv == GL_FALSE) {
    int length;
    glGetShaderiv(result, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(result, length, &length, message);
    std::cout << message << std::endl;
    glDeleteShader(result);
  }
  return result;
}

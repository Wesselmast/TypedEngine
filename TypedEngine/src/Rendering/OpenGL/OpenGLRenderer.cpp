#include "OpenGLRenderer.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/gtx/quaternion.hpp"

//@CleanUp: Make own error logging function and include that instead;
#include <stdio.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "OpenGLShader.h"
#include "OpenGLTexture.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexArray.h"


//@CleanUp: This text stuff all has to be abstracted, for now this is where it'll live!

void OpenGLRenderer::init(Camera* camera) {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD");
    return;
  }

  FT_Library ft;
  if(FT_Init_FreeType(&ft)) {
    fprintf(stderr, "Failed to initialize FreeType");
    return;
  }
  
  setBlending(true);

  setCamera(camera);
  setDefaultShader(new OpenGLShader("res/shaders/default.shader"));
  
  float vertices[] = {
     //pos	   //texcoord
     -1.0,  1.0,   0.0f,  1.0f,
      1.0,  1.0,   1.0f,  1.0f,
      1.0, -1.0,   1.0f,  0.0f,
     -1.0, -1.0,   0.0f,  0.0f
  };
  
  unsigned int vertexBufferLayout[] = {
     2, 2
  };
  
  unsigned int indices[] = {
     0, 1, 2,
     2, 3, 0
  };

  vertexArray = new OpenGLVertexArray();
  vertexBuffer = new OpenGLVertexBuffer(vertices, sizeof vertices);
  indexBuffer = new OpenGLIndexBuffer(indices, sizeof indices);
  
  vertexBuffer->setLayout(vertexBufferLayout, sizeof vertexBufferLayout);
  
  vertexArray->setVertexBuffer(vertexBuffer);
  vertexArray->setIndexBuffer(indexBuffer);
	
  vertexArray->bind();
}

void OpenGLRenderer::run() {
  for(Sprite* d : drawables) {
    drawSprite(d->transform, d->texture);
  }
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

void OpenGLRenderer::drawSprite(Transform transform, Texture * texture) {
  texture->bind();
  
  vertexArray->bind();
  
  getDefaultShader()->bind();
  getDefaultShader()->setUniformMat4("uMvpMatrix", calculateMVPFromTransform(transform));
  getDefaultShader()->setUniformInt1("uTexture", 0);
  
  glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
}

glm::mat4 OpenGLRenderer::calculateMVPFromTransform(Transform transform) {
  glm::mat4 position = glm::translate(glm::mat4(1.0f), glm::vec3(transform.position, 0.0f));
  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), transform.rotation, glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(transform.scale, 1.0f));
  
  glm::mat4 model = position * rotation * scale;
  glm::mat4 mvp = getCamera()->getViewProjection() * model;
  return mvp;
}

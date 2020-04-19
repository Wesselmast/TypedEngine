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

#include <map>
#include <utility>
#include <string>
#include <iostream>

//@CleanUp: This text stuff all has to be abstracted, for now this is where it'll live!

struct Character {
  GLuint textureID;
  glm::ivec2 size;
  glm::ivec2 bearing;
  GLuint advance;
};

std::map<GLchar, Character> characters;
OpenGLShader* defaultTextShader;

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

  FT_Face face;
  if(FT_New_Face(ft, "res/fonts/Menlo-Regular.ttf", 0, &face)) {
    fprintf(stderr, "Failed to load font Menlo-Regular.ttf");
    return;
  }

  FT_Set_Pixel_Sizes(face, 0, 48); //0 is automatically deciding width, 48 is height

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for(GLubyte c = 0; c < 128; c++) {
    if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      fprintf(stderr, "Failed to load character");
      continue;
    }
    
    GLuint fontTextureID;
    glGenTextures(1, &fontTextureID);
    glBindTexture(GL_TEXTURE_2D, fontTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    Character character = { fontTextureID, { face->glyph->bitmap.width, face->glyph->bitmap.rows }, { face->glyph->bitmap_left, face->glyph->bitmap_top }, face->glyph->advance.x };
    characters.insert(std::pair<GLchar, Character>(c, character));
  }
  glBindTexture(GL_TEXTURE_2D, 0);
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
  
  
  setBlending(true);

  setCamera(camera);
  setDefaultShader(new OpenGLShader("res/shaders/default.shader"));
  defaultTextShader = new OpenGLShader("res/shaders/defaultText.shader");

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

  vertexArrayT = new OpenGLVertexArray();
  vertexBufferT = new OpenGLVertexBuffer(vertices, sizeof vertices);
  indexBufferT = new OpenGLIndexBuffer(indices, sizeof indices);
  
  vertexBufferT->setLayout(vertexBufferLayout, sizeof vertexBufferLayout);
  
  vertexArrayT->setVertexBuffer(vertexBufferT);
  vertexArrayT->setIndexBuffer(indexBufferT);

  vertexArrayT->bind();
}

void OpenGLRenderer::run() {
  for(Sprite* d : drawables) {
    drawSprite(d->transform, d->texture);
  }

  // yet more text stuff that needs to be moved!

  drawText();
  
}

void OpenGLRenderer::drawText() {
  std::string text = "Dag, Wessel!";
  Transform transform = { { 25.0f, 25.0f }, 0.0f, { 5.0f, 5.0f } };

  defaultTextShader->bind();
  defaultTextShader->setUniformMat4("uMvpMatrix", calculateMVPFromTransform(transform));
  defaultTextShader->setUniformFloat4("textColor", { 1.0f, 0.0f, 0.0f, 1.0f });
  glActiveTexture(GL_TEXTURE0);
  vertexArrayT->bind();

  GLfloat x = transform.position.x;
  GLfloat y = transform.position.y;
  glm::vec2 s = transform.scale;
  
  std::string::const_iterator c;
  for(c = text.begin(); c != text.end(); c++) {
    Character ch = characters[*c];

    GLfloat xpos = x + ch.bearing.x * s.x;
    GLfloat ypos = y - (ch.size.y - ch.bearing.y) * s.y;

    GLfloat w = ch.size.x * s.x;
    GLfloat h = ch.size.y * s.y;

    GLfloat vertices[] = {
       xpos,     ypos,       0.0f, 1.0f,
       xpos + w, ypos,       1.0f, 1.0f,
       xpos + w, ypos + h,   1.0f, 0.0f,
       xpos,     ypos + h,   0.0f, 0.0f,
    };
    
    glBindTexture(GL_TEXTURE_2D, ch.textureID);
    vertexBufferT->bind();
    vertexBufferT->addSubData(vertices, sizeof(vertices));
    vertexBufferT->unbind();
    
    glDrawElements(GL_TRIANGLES, vertexArrayT->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, 0);
    x += (ch.advance >> 6) * s.x;
  }
  vertexArrayT->unbind();
  glBindTexture(GL_TEXTURE_2D, 0);
  defaultTextShader->unbind();
}

void OpenGLRenderer::setBlending(bool enabled) {
  if (enabled) {
    // @CleanUp: Culling should be in a separate function
    glEnable(GL_CULL_FACE);
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
  transform.scale.x *= -1.0f;
  
  vertexArray->bind();
  
  getDefaultShader()->bind();
  getDefaultShader()->setUniformMat4("uMvpMatrix", calculateMVPFromTransform(transform));
  
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

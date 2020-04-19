#pragma once
#include "../Renderer.h"

class OpenGLRenderer : public Renderer {
public:
  virtual void init(Camera* camera) override;
  virtual void setBlending(bool enabled) override;
  
  virtual void clear(glm::vec4 color) override;
  virtual void drawSprite(Transform transform, Texture * texture) override;
  
  void drawQuad(Transform transform, glm::vec4 color);
  void drawText(std::string text, Transform transform);
  
  virtual void run() override;
  
  ~OpenGLRenderer() {
    delete vertexArray;
    delete vertexBuffer;
    delete indexBuffer;
    //Renderer::~Renderer();
  }

private:
  glm::mat4 calculateMVPFromTransform(Transform transform);

private:
  VertexArray* vertexArray;
  VertexBuffer* vertexBuffer;
  IndexBuffer* indexBuffer;
  VertexArray* vertexArrayT;
  VertexBuffer* vertexBufferT;
  IndexBuffer* indexBufferT;
  VertexArray* vertexArrayQ;
  VertexBuffer* vertexBufferQ;
  IndexBuffer* indexBufferQ;
};

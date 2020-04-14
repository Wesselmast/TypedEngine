#pragma once
#include "../Renderer.h"

class OpenGLRenderer : public Renderer {
public:
  virtual void init(Camera* camera) override;
  virtual void setBlending(bool enabled) override;
  
  virtual void clear(glm::vec4 color) override;
  virtual void drawSprite(Transform transform, Texture * texture) override;

  virtual void run() override;
  
  ~OpenGLRenderer() {
    delete vertexArray;
    delete vertexBuffer;
    delete indexBuffer;
    Renderer::~Renderer();
  }

private:
  glm::mat4 calculateMVPFromTransform(Transform transform);

private:
  VertexArray* vertexArray;
  VertexBuffer* vertexBuffer;
  IndexBuffer* indexBuffer;
};

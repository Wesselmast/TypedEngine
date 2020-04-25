#pragma once
#include "../Renderer.h"

class VertexArray;
class VertexBuffer;
class IndexBuffer;

struct Transform;

class OpenGLRenderer : public Renderer {
public:
  virtual void init(Camera* camera) override;
  virtual void setBlending(bool enabled) override;
  virtual void setCulling(bool enabled) override;
  
  virtual void clear(glm::vec4 color) override;
  virtual void drawSprite(Sprite* sprite) override;
  virtual void drawText(Text* text) override;
  virtual void drawQuad(Quad* quad) override;
  
  virtual void run() override;
  
  ~OpenGLRenderer();
private:
  glm::mat4 calculateMVPFromTransform(Transform transform, bool onlyProj = false);

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

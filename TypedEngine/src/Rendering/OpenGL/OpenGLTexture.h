#pragma once

#include "../Texture.h"

class OpenGLTexture : public Texture {
public:
  OpenGLTexture(const char* path);
  ~OpenGLTexture();
  
  virtual void bind(unsigned int slot) override;
  virtual void unbind() override;
  
  virtual int getWidth() const override;
  virtual int getHeight() const override;
};

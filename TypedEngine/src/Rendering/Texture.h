#pragma once

class Texture {
public:
  virtual ~Texture() = default;
  
  virtual int getWidth() const = 0;
  virtual int getHeight() const = 0;
  
  virtual void bind(unsigned int slot = 0) = 0;
  virtual void unbind() = 0;
  
  bool valid = false;
protected:
  unsigned int rendererID;
  int width;
  int height;
};

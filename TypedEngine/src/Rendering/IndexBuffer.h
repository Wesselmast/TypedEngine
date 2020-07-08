#pragma once

class IndexBuffer {
public:
  virtual ~IndexBuffer() = default;
  
  virtual void bind() = 0;
  virtual void unbind() = 0;
  
  virtual unsigned int getCount() const = 0;

protected:
  unsigned int count;
  unsigned int rendererID;
  
};

#pragma once

#include "../IndexBuffer.h"

class OpenGLIndexBuffer : public IndexBuffer {
public:
	OpenGLIndexBuffer(unsigned int* indices, unsigned int size);
	~OpenGLIndexBuffer();

	virtual void bind() override;
	virtual void unbind() override;
	virtual unsigned int getCount() const override;
};


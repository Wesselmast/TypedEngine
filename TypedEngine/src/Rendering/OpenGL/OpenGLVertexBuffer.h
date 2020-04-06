#pragma once

#include "../VertexBuffer.h"

class OpenGLVertexBuffer : public VertexBuffer {
public:
	OpenGLVertexBuffer(float* vertices, unsigned int size);
	~OpenGLVertexBuffer();

	virtual void bind() override;
	virtual void unbind() override;
};
#pragma once

#include "../VertexArray.h"

class OpenGLVertexArray : public VertexArray {
public:
	OpenGLVertexArray();
	~OpenGLVertexArray();

	virtual void setVertexBuffer(VertexBuffer* vertexBuffer) override;
	virtual void setIndexBuffer(IndexBuffer* indexBuffer) override;
	virtual void bind() override;
	virtual void unbind() override;
};
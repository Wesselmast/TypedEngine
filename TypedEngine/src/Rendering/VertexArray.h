#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class VertexArray {
public:
	virtual ~VertexArray() = default;

	virtual void setVertexBuffer(VertexBuffer* vertexBuffer) = 0;
	virtual void setIndexBuffer(IndexBuffer* indexBuffer) = 0;

	inline VertexBuffer* getVertexBuffer() const {
		return vertexBuffer;
	}
	inline IndexBuffer* getIndexBuffer() const {
		return indexBuffer;
	}

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	unsigned int rendererID;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;

};
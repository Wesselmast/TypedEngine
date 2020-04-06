#pragma once

class VertexBuffer {
public:
	virtual ~VertexBuffer() = default;

	virtual void bind() = 0;
	virtual void unbind() = 0;

protected:
	unsigned int rendererID;

};
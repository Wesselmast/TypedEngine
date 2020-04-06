#pragma once

class Texture {
public:
	virtual ~Texture() = default;

	virtual void bind(unsigned int slot = 0) = 0;
	virtual void unbind() = 0;

protected:
	unsigned int rendererID;
};
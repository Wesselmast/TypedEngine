#pragma once

#include "../Texture.h"

class OpenGLTexture : public Texture {
public:
	OpenGLTexture(const char* path);
	~OpenGLTexture();

	// Inherited via Texture
	virtual void bind(unsigned int slot) override;
	virtual void unbind() override;
};

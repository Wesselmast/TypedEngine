#include "OpenGLTexture.h"

#include <GL/glew.h>

#include "stb_image/stb_image.h"

OpenGLTexture::OpenGLTexture(const char * path) {
	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(1);

	int width, height, colorChannels;
	unsigned char* data = stbi_load(path, &width, &height, &colorChannels, 4);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		fprintf(stderr, "Error: Texture is not valid");
	}
	stbi_image_free(data);
}

OpenGLTexture::~OpenGLTexture() {
	glDeleteTextures(1, &rendererID);
}

void OpenGLTexture::bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}

void OpenGLTexture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

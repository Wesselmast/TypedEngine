#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct ShaderProgramSource {
	const char* vertex;
	const char* fragment;

	~ShaderProgramSource() {
		delete vertex;
		delete fragment;
	}
};

class Shader {
public:
	virtual ~Shader() = default;

	virtual void run() = 0;

	virtual void setUniformFloat4(const char* name, glm::vec4 value) = 0;
	virtual void setUniformMat4(const char* name, glm::mat4 value) = 0;
	virtual void setUniformSampler(const char* name, int id) = 0;

protected:
	static void parseShader(const char* path, ShaderProgramSource* source);
private:
	static char* filterShaderCommands(const char* createCommand, const char* deleteCommand, char* buffer);

protected:
	unsigned int rendererID;
	ShaderProgramSource source;
};

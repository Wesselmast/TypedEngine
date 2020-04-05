#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

struct ShaderProgramSource {
	const char* vertex;
	const char* fragment;

	~ShaderProgramSource() {
		delete vertex;
		delete fragment;
	}
};

glm::vec2 input = glm::vec2(0, 0);
float zoomInput = 0;

static char* filterShaderCommands(const char* createCommand, const char* deleteCommand, char* buffer) {
	char* result = nullptr;

	const char* start = std::strstr(std::strstr(buffer, createCommand), "\n");
	if (start) {
		const char* end = std::strstr(start, deleteCommand);
		if (end) {
			size_t len = end - start;
			result = (char*)malloc(len + 1);
			if (result) {
				memcpy(result, start, len);
				result[len] = 0;
			}
		}
	}
	if (!result) {
		fprintf(stderr, "Error: Was not able to filter given shader commands");
	}
	return result;
}

static void parseShader(const char* path, ShaderProgramSource* source) {
	FILE* shaderFile;
	fopen_s(&shaderFile, path, "r");

	if (shaderFile == NULL) {
		fprintf(stderr, "Error: Shader file was not found.");
		std::cin.get();
	}

	char* buffer = nullptr;
	fseek(shaderFile, 0, SEEK_END);
	long length = ftell(shaderFile);
	fseek(shaderFile, 0, SEEK_SET);
	
	buffer = (char*)malloc(length + 1);
	if (buffer) {
		fread(buffer, 1, length, shaderFile);
	}
	fclose(shaderFile);
	buffer[length] = '\0';
	
	if (buffer) {
		source->vertex   = filterShaderCommands("#shader vertex",	"#endshader vertex",   buffer);
		source->fragment = filterShaderCommands("#shader fragment", "#endshader fragment", buffer);
	}

	fclose(shaderFile);
	delete buffer;
	delete shaderFile;
}

static void errorCallback(int error, const char* message) {
	fprintf(stderr, "Error %d: %s\n", error, message);
}

static void recieveInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
		return;
	}
	if (action == GLFW_PRESS) {
		switch (key) {
			case GLFW_KEY_W: input.y =  1.0f; break;
			case GLFW_KEY_S: input.y = -1.0f; break;
			case GLFW_KEY_A: input.x = -1.0f; break;
			case GLFW_KEY_D: input.x =  1.0f; break;
			case GLFW_KEY_Q: zoomInput	 =  1.0f; break;
			case GLFW_KEY_E: zoomInput	 = -1.0f; break;
			default: input = glm::vec2(0, 0); zoomInput = 0;
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_W: input.y = 0.0f; break;
			case GLFW_KEY_S: input.y = 0.0f; break;
			case GLFW_KEY_A: input.x = 0.0f; break;
			case GLFW_KEY_D: input.x = 0.0f; break;
			case GLFW_KEY_Q: zoomInput	 = 0.0f; break;
			case GLFW_KEY_E: zoomInput	 = 0.0f; break;
		}
	}
}

int main() {
	ShaderProgramSource source;
	parseShader("res\\shaders\\object.shader", &source);
	GLint vlen = strlen(source.vertex);
	GLint flen = strlen(source.fragment);

	glm::vec2 vertices[4] = {
		{ -0.5f,  0.5f },
		{  0.5f,  0.5f },
		{  0.5f, -0.5f },
		{ -0.5f, -0.5f }
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint vbo, ib, vs, fs, program;
	GLuint colorLocation, mvpMatrixLocation;

	const unsigned short WIDTH = 640;
	const unsigned short HEIGHT = 480;
	const glm::vec2 ASPECT(((float)WIDTH / (float)HEIGHT), ((float)HEIGHT / (float)WIDTH));

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model = glm::mat4(1.0f);

	/* init glfw */

	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "TestWindow", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, recieveInput);
	glfwSetErrorCallback(errorCallback);
	glfwSwapInterval(1);

	glewInit();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &source.vertex, &vlen);
	glCompileShader(vs);

	GLint result;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(vs, length, &length, message);
		std::cout << message << std::endl;
		glDeleteShader(vs);
	}


	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &source.fragment, &flen);
	glCompileShader(fs);

	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(vs, length, &length, message);
		std::cout << message << std::endl;
		glDeleteShader(vs);
	}


	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	colorLocation = glGetUniformLocation(program, "uColor");
	mvpMatrixLocation = glGetUniformLocation(program, "uMvpMatrix");

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glVertexAttribPointer(0, sizeof(glm::vec2) / sizeof(float), GL_FLOAT, GL_FALSE, 0, 0);

	float previous = glfwGetTime();
	glm::vec3 position = glm::vec3(0,0,0);
	float zoom = 1;

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		float deltaTime = time - previous;

		GLsizei width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(50 / 255.0f, 47 / 255.0f, 44 / 255.0f, 1.0f);
		glUniform4f(colorLocation, 142 / 255.0f, 104 / 255.0f, 70 / 255.0f, 1.0f);
	
		float zoomSpeed = 3.0f;

		zoom += zoomInput * deltaTime * zoomSpeed;
		if (zoom <= 0.001f) {
			zoom = 0.001f;
		}
		else if (zoom >= 10) {
			zoom = 10;
		}
		projection = glm::ortho(-ASPECT.x * zoom, ASPECT.x * zoom, -ASPECT.y * zoom, ASPECT.y * zoom, -1.0f, 1.0f);

		position += glm::vec3(input, 0.0f) * deltaTime * zoom;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		view = glm::inverse(transform);

		glm::mat4 mvp = projection * view * model;
		glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvp[0][0]);

		/* render something simple! */
		glUseProgram(program);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		previous = time;
	}

	glDeleteProgram(program);

	glfwTerminate();
	return 0;
}
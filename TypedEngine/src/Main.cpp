#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Rendering/OpenGL/OpenGLShader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

#include "stb_image/stb_image.h"

glm::vec2 input = glm::vec2(0, 0);
float zoomInput = 0;

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
			case GLFW_KEY_W: input.y   =  1.0f; break;
			case GLFW_KEY_S: input.y   = -1.0f; break;
			case GLFW_KEY_A: input.x   = -1.0f; break;
			case GLFW_KEY_D: input.x   =  1.0f; break;
			case GLFW_KEY_Q: zoomInput =  1.0f; break;
			case GLFW_KEY_E: zoomInput = -1.0f; break;
			default: input = glm::vec2(0, 0); zoomInput = 0;
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_W: input.y   =  0.0f; break;
			case GLFW_KEY_S: input.y   =  0.0f; break;
			case GLFW_KEY_A: input.x   =  0.0f; break;
			case GLFW_KEY_D: input.x   =  0.0f; break;
			case GLFW_KEY_Q: zoomInput =  0.0f; break;
			case GLFW_KEY_E: zoomInput =  0.0f; break;
		}
	}
}

int main() {
	std::unique_ptr<Shader> shader;

	const float vertices[] = {
		//pos			//texcoord
		-0.5f,  0.5f,	0.0f,  1.0f,
		 0.5f,  0.5f,	1.0f,  1.0f,
		 0.5f, -0.5f,	1.0f,  0.0f,
		-0.5f, -0.5f,	0.0f,  0.0f
	};

	const unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint vbo, ib, vao;
	GLuint colorLocation, mvpMatrixLocation, textureLocation;

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

	shader = std::make_unique<OpenGLShader>("res/shaders/object.shader");


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/* TEXTURE */
	glGenTextures(1, &textureLocation);
	glBindTexture(GL_TEXTURE_2D, textureLocation);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(1);

	int texWidth, texHeight, colorChannels;
	unsigned char* data = stbi_load("res/textures/T_Brick.jpg", &texWidth, &texHeight, &colorChannels, 4);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "texture not loaded";
	}
	stbi_image_free(data);


	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(1);

	float previous = (float)glfwGetTime();
	glm::vec3 position = glm::vec3(0,0,0);
	float zoom = 1;

	while (!glfwWindowShouldClose(window))
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
		glBindTexture(GL_TEXTURE_2D, textureLocation);

		float time = (float)glfwGetTime();
		float deltaTime = time - previous;

		GLsizei width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1.0f, 207.0f / 255.0f, 207.0f / 255.0f, 1.0f);

		glm::vec4 color(142 / 255.0f, 104 / 255.0f, 70 / 255.0f, 1.0f);


		float zoomSpeed = 3.0f;

		zoom += zoomInput * deltaTime * zoomSpeed;
		if (zoom <= 0.01f) {
			zoom = 0.01f;
		}
		else if (zoom >= 10) {
			zoom = 10;
		}
		projection = glm::ortho(-ASPECT.x * zoom, ASPECT.x * zoom, -ASPECT.y * zoom, ASPECT.y * zoom, -1.0f, 1.0f);

		position += glm::vec3(input, 0.0f) * deltaTime * zoom;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		view = glm::inverse(transform);

		glm::mat4 mvp = projection * view * model;

		shader->setUniformFloat4("uColor", color);
		shader->setUniformMat4("uMvpMatrix", mvp);
		shader->setUniformSampler("uTexture", 0);

		/* render something simple! */
		shader->run();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		previous = time;
	}

	glfwTerminate();
	return 0;
}
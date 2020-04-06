#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Rendering/OpenGL/OpenGLShader.h"
#include "Rendering/OpenGL/OpenGLTexture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>

glm::vec2 input = glm::vec2(0, 0);
float zoomInput = 0;

static void errorCallback(int error, const char* message) {
	fprintf(stderr, "Error %d: %s\n", error, message);
}


/* INPUT POLLING STUFF */
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

	/* WINDOW STUFF @Important: look at how I want to separate these */
	const unsigned short WIDTH = 640;
	const unsigned short HEIGHT = 480;
	const glm::vec2 ASPECT(((float)WIDTH / (float)HEIGHT), ((float)HEIGHT / (float)WIDTH));

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


	std::unique_ptr<Shader> shader = std::make_unique<OpenGLShader>("res/shaders/object.shader");
	shader->bind();

	/* VERTEX ARRAY */
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* VERTEX BUFFER */
	const float vertices[] = {
		//pos			//texcoord
		-0.5f,  0.5f,	0.0f,  1.0f,
		 0.5f,  0.5f,	1.0f,  1.0f,
		 0.5f, -0.5f,	1.0f,  0.0f,
		-0.5f, -0.5f,	0.0f,  0.0f
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
	glEnableVertexAttribArray(0);

	/* INDEX BUFFER */
	const unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLuint ib;
	glGenBuffers(1, &ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(1);
	

	std::unique_ptr<Texture> textureBrick = std::make_unique<OpenGLTexture>("res/textures/T_Brick.jpg");
	std::unique_ptr<Texture> textureTree = std::make_unique<OpenGLTexture>("res/textures/T_Tree.png");

	/* @CleanUp: this is just random crap*/

	float previous = (float)glfwGetTime();
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec4 objectColor(142 / 255.0f, 104 / 255.0f, 70 / 255.0f, 1.0f); //@Unused: Unused variable but nice color :)
	glm::vec4 clearColor(1.0f, 207.0f / 255.0f, 207.0f / 255.0f, 1.0f);
	float zoomSpeed = 3.0f;
	float zoom = 1;
	
	/* RENDERING */

	while (!glfwWindowShouldClose(window)) {

		/* DELTATIME STUFF */
		float time = (float)glfwGetTime();
		float deltaTime = time - previous;

		/* WINDOW STUFF */
		GLsizei width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		/* @CleanUp: This zooming stuf is done directly into the othrographic calculation. Find better way of doing this */
		zoom += zoomInput * deltaTime * zoomSpeed;
		if (zoom <= 0.01f) {
			zoom = 0.01f;
		}
		else if (zoom >= 10) {
			zoom = 10;
		}

		/* CAMERA STUFF */
		glm::mat4 projection = glm::ortho(-ASPECT.x * zoom, ASPECT.x * zoom, -ASPECT.y * zoom, ASPECT.y * zoom, -1.0f, 1.0f);
		
		position += glm::vec3(input, 0.0f) * deltaTime * zoom;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 view = glm::inverse(transform);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 mvp = projection * view * model;


		/* RENDERER STUFF */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);

		/* SHADER RUNTIME STUFF */
		shader->bind();
		textureTree->bind();
		shader->setUniformMat4("uMvpMatrix", mvp);
		shader->setUniformInt1("uTexture", 0);

		/* RUNTIME BINDING: SHOULD BE IN RENDERER CLASS */
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* WINDOW STUFF */
		glfwSwapBuffers(window);
		glfwPollEvents();

		/* Unbind */
		shader->unbind();
		textureTree->unbind();

		//
		previous = time;
	}

	glfwTerminate();
	return 0;
}
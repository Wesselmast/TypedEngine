#include <GLFW/glfw3.h>

#include "Rendering/OpenGL/OpenGLShader.h"
#include "Rendering/OpenGL/OpenGLTexture.h"
#include "Rendering/OpenGL/OpenGLIndexBuffer.h"
#include "Rendering/OpenGL/OpenGLVertexBuffer.h"
#include "Rendering/OpenGL/OpenGLVertexArray.h"
#include "Rendering/RenderCommand.h"
#include "Rendering/Camera.h"

#include "glm/glm.hpp"

#include <iostream>

glm::vec2 input = glm::vec2(0, 0);
float zoom = 1;

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
			default: input = glm::vec2(0, 0);
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
			case GLFW_KEY_W: input.y   =  0.0f; break;
			case GLFW_KEY_S: input.y   =  0.0f; break;
			case GLFW_KEY_A: input.x   =  0.0f; break;
			case GLFW_KEY_D: input.x   =  0.0f; break;
		}
	}
}

static void scrollInput(GLFWwindow* window, double xoffset, double yoffset) {
	zoom += -yoffset * 0.5f; // x = zoomspeed
	if (zoom <= 0.01f) {
		zoom = 0.1f;
	}
	else if (zoom >= 10) {
		zoom = 10;
	}
}

int main() {

	/* WINDOW STUFF @Important: look at how I want to separate these
					@CleanUp: make the width and height values the width and height of the current monitor
	*/
	const unsigned short WIDTH = 640;
	const unsigned short HEIGHT = 480;

	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "TestWindow", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, recieveInput);
	glfwSetScrollCallback(window, scrollInput);
	glfwSwapInterval(1); //complex name, just vSync
	
	
	Camera* camera = new Camera(window);

	RenderCommand::init(camera);

	Texture* texture = new OpenGLTexture("res/textures/T_Tree.png");

	float vertices[] = {
		//pos		  //texcoord
		-1.0,  1.0,   0.0f,  1.0f,
		 1.0,  1.0,   1.0f,  1.0f,
		 1.0, -1.0,   1.0f,  0.0f,
		-1.0, -1.0,   0.0f,  0.0f
	};

	unsigned int vertexBufferLayout[] = {
		2, 2
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray* vertexArray = new OpenGLVertexArray();
	VertexBuffer* vertexBuffer = new OpenGLVertexBuffer(vertices, sizeof vertices);
	IndexBuffer* indexBuffer = new OpenGLIndexBuffer(indices, sizeof indices);

	vertexBuffer->setLayout(vertexBufferLayout, sizeof vertexBufferLayout);

	vertexArray->setVertexBuffer(vertexBuffer);
	vertexArray->setIndexBuffer(indexBuffer);

	vertexArray->bind();


	/* @CleanUp: this is just random crap */

	float previous = (float)glfwGetTime();
	glm::vec2 position = glm::vec3(0, 0, 0);
	float rotation = 0.0f;
	glm::vec4 objectColor(142 / 255.0f, 104 / 255.0f, 70 / 255.0f, 1.0f); //@Unused: Unused variable but nice color :)
	glm::vec4 clearColor(233/255.0f, 233 / 255.0f, 245 / 255.0f, 1.0f);
	const float rotSpeed = 3.0f;
	const float panSpeed = 750.0f;


	/* RENDERING */
	while (!glfwWindowShouldClose(window)) {

		/* DELTATIME STUFF */
		float time = (float)glfwGetTime();
		float deltaTime = time - previous;
		std::cout << 1/deltaTime << std::endl;

		/* WINDOW STUFF @CleanUp: Really ugly. This is done twice a frame now due to the camera system */
		GLsizei width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);


		position += input * deltaTime * zoom * panSpeed;
		camera->setPosition(position);
		camera->setScale(glm::vec2(zoom));


		RenderCommand::clear(clearColor);

		//ToDo @Optimization: Add a camera object and check if transforms are in camera viewport (if not, cull them)
		for (int i = 0; i < 2; i++)
		{
			//ToDo @CleanUp: Rotation is reduntant, just make it a float, also its broken
			Transform transform = { { 1024.0f * i, 0.0f }, 0.0f, { 1.0f, 1.0f} };

			//ToDo @CleanUp: - drawSprite can problably get to a stage where you only need the transform and an optional texture
			//				 - get to a point where I just have to 'create' a sprite at some point and have the back-end push it onto a runtime loop (hide rendering)
			RenderCommand::drawSprite(transform, vertexArray);
		}

		{
			Transform transform = { { 1000, 1250.0f }, 0.0f, { 1.0f, 1.0f } };
			RenderCommand::drawSprite(transform, vertexArray, texture);
		}

		/* WINDOW STUFF */
		glfwSwapBuffers(window);
		glfwPollEvents();


		/* Unbind */
		//IMPORTANT @CleanUp: Shader doesn't get unbound
	/*	texture->unbind();
		vertexArray->unbind();*/

		//
		previous = time;
	}

	glfwTerminate();

	delete texture;
	delete vertexArray;
	delete vertexBuffer;
	delete indexBuffer;
	delete camera;
	return 0;
}
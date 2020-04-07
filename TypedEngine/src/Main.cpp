#include <GLFW/glfw3.h>

#include "Rendering/OpenGL/OpenGLShader.h"
#include "Rendering/OpenGL/OpenGLTexture.h"
#include "Rendering/OpenGL/OpenGLIndexBuffer.h"
#include "Rendering/OpenGL/OpenGLVertexBuffer.h"
#include "Rendering/OpenGL/OpenGLVertexArray.h"
#include "Rendering/RenderCommand.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>

glm::vec2 input = glm::vec2(0, 0);
float zoomInput = 0;

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

	/* WINDOW STUFF @Important: look at how I want to separate these
					@CleanUp: make the width and height values the width and height of the current monitor
	*/
	const unsigned short WIDTH = 1920;
	const unsigned short HEIGHT = 1080;
	const glm::vec2 ASPECT((float)WIDTH, (float)HEIGHT);

	if (!glfwInit()) return -1;

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "TestWindow", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, recieveInput);
	glfwSwapInterval(1);		//just vSync
	
	
	RenderCommand::init();

	Shader* shader = new OpenGLShader("res/shaders/object.shader");
	Texture* texture = new OpenGLTexture("res/textures/T_Brick.jpg");
	Texture* textureTree = new OpenGLTexture("res/textures/T_Tree.png");

	float vertices[] = {
		//pos														//texcoord
		-(float)texture->getWidth(),  (float)texture->getHeight(),	0.0f,  1.0f,
		 (float)texture->getWidth(),  (float)texture->getHeight(),	1.0f,  1.0f,
		 (float)texture->getWidth(), -(float)texture->getHeight(),	1.0f,  0.0f,
		-(float)texture->getWidth(), -(float)texture->getHeight(),	0.0f,  0.0f
	};

	float verticesTree[] = {
		//pos														//texcoord
		-(float)textureTree->getWidth(),  (float)textureTree->getHeight(),	0.0f,  1.0f,
		 (float)textureTree->getWidth(),  (float)textureTree->getHeight(),	1.0f,  1.0f,
		 (float)textureTree->getWidth(), -(float)textureTree->getHeight(),	1.0f,  0.0f,
		-(float)textureTree->getWidth(), -(float)textureTree->getHeight(),	0.0f,  0.0f
	};

	unsigned int vertexBufferLayout[] = {
		2, 2
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray* vertexArray = new OpenGLVertexArray();
	VertexArray* vertexArrayTree = new OpenGLVertexArray();
	VertexBuffer* vertexBuffer = new OpenGLVertexBuffer(vertices, sizeof vertices);
	VertexBuffer* vertexBufferTree = new OpenGLVertexBuffer(verticesTree, sizeof verticesTree);
	IndexBuffer* indexBuffer = new OpenGLIndexBuffer(indices, sizeof indices);

	vertexBufferTree->setLayout(vertexBufferLayout, sizeof vertexBufferLayout);
	vertexBuffer->setLayout(vertexBufferLayout, sizeof vertexBufferLayout);

	vertexArrayTree->setVertexBuffer(vertexBufferTree);
	vertexArrayTree->setIndexBuffer(indexBuffer);
	vertexArray->setVertexBuffer(vertexBuffer);
	vertexArray->setIndexBuffer(indexBuffer);

	vertexArrayTree->bind();
	vertexArray->bind();


	/* @CleanUp: this is just random crap*/

	float previous = (float)glfwGetTime();
	glm::vec3 position = glm::vec3(0,0,0);
	glm::vec4 objectColor(142 / 255.0f, 104 / 255.0f, 70 / 255.0f, 1.0f); //@Unused: Unused variable but nice color :)
	glm::vec4 clearColor(233/255.0f, 233 / 255.0f, 245 / 255.0f, 1.0f);
	const float zoomSpeed = 3.0f;
	const float panSpeed = 500.0f;
	float zoom = 1;
	
	/* RENDERING */
	while (!glfwWindowShouldClose(window)) {

		/* DELTATIME STUFF */
		float time = (float)glfwGetTime();
		float deltaTime = time - previous;
		std::cout << 1/deltaTime << std::endl;

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
		
		position += glm::vec3(input, 0.0f) * deltaTime * zoom * panSpeed;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 view = glm::inverse(transform);


		RenderCommand::clear(clearColor);

		for (int i = 0; i < 2; i++)
		{
			//ToDo @CleanUp: Rotation is reduntant, just make it a float, also its broken
			Transform transform = { { 1024.0f * i, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
			RenderCommand::drawSprite(texture, shader, transform, projection * view, vertexArray);
		}

		{
			Transform transform = { { 1000, 1250.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } };
			RenderCommand::drawSprite(textureTree, shader, transform, projection * view, vertexArrayTree);
		}

		/* WINDOW STUFF */
		glfwSwapBuffers(window);
		glfwPollEvents();

		/* Unbind */
		shader->unbind();
		texture->unbind();
		textureTree->unbind();
		vertexArray->unbind();
		vertexArrayTree->unbind();

		//
		previous = time;
	}

	glfwTerminate();

	delete shader;
	delete texture;
	delete textureTree;
	delete vertexArray;
	delete vertexArrayTree;
	delete vertexBuffer;
	delete vertexBufferTree;
	delete indexBuffer;
	return 0;
}
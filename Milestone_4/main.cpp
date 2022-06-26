#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.h"
#include "error.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include <vector>
#include "vertexAttribVector.h"
#include "renderer.h"


static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GLCheckError(glViewport(0, 0, width, height));
}

static void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static void RenderLoop(GLFWwindow* window, VertexArray& vertexArray, Shader& shader) {
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		Renderer renderer;

		// Clear color buffer
		renderer.Clear(0.1f, 0.1f, 0.2f, 1.0f);

		shader.use();
		vertexArray.bind();

		// Uniform
		float timeValue = glfwGetTime();
		float blueColorValue = sin(timeValue) / 4.0f + 0.75f;
		shader.SetUniform1f("blueColor", blueColorValue);

		renderer.Draw(vertexArray, shader);

		// Double buffering
		glfwSwapBuffers(window);

		// Process events e.g. keyboard
		glfwPollEvents();
	}

	glfwTerminate();
}

int main(void)
{
	GLFWwindow* window;

	// Initialise GLFW
	if (!glfwInit()) {
		std::cout << "Failed to initialised GLFW" << std::endl;
		return -1;
	}

	// Version 4.1 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	window = glfwCreateWindow(640, 480, "Toy OpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl
;		return -1;
	}

	// Vertex Data
	float vertexData[] = {
		 // position   // color
		 0.5f,  0.5f,  0.2f, 0.3f, 0.8f,  // top right
		 0.5f, -0.5f,  0.4f, 0.8f, 0.4f,  // bottom right
		-0.5f, -0.5f,  0.7f, 0.6f, 0.8f,  // bottom left
		-0.5f,  0.5f,  0.9f, 0.4f, 0.6f,  // top left
	};

	// EBO
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	// VAO
	VertexAttribVector vertexAttribVector;
	vertexAttribVector.Push<float>(2, false);
	vertexAttribVector.Push<float>(3, false);
	VertexArray vertexArray = VertexArray((void*)vertexData, 4 * vertexAttribVector.GetStride(), indices, 6, vertexAttribVector);

	// Shader
	Shader shader = Shader("shader/vertex.vs", "shader/fragment.fs");

	RenderLoop(window, vertexArray, shader);

	return 0;
}
#include <iostream>
// #include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "shader.h"
#include "error.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
// #include <array>
#include <vector>


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

		// Clear color buffer
		GLCheckError(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		GLCheckError(glClear(GL_COLOR_BUFFER_BIT));

		shader.use();
		vertexArray.bind();

		// Uniform
		float timeValue = glfwGetTime();
		float blueColorValue = sin(timeValue) / 4.0f + 0.75f;
		unsigned int vertexColorLocation = glGetUniformLocation(shader.ID, "blueColor");
		GLCheckError(glUniform1f(vertexColorLocation, blueColorValue));

		// With VBO (drawing a triangle)
		// Draw mode; starting index of array; no. verticies
		// GLCheckError(glDrawArrays(GL_TRIANGLES, 0, 6));

		// With EBO (drawing a rectangle)
		// Draw mode; no. indices; type of indices; offset
		GLCheckError(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

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

	// float vertexData[] = {
	// 	 // position    // color
	// 	 -0.5f, -0.5f,  0.2f, 0.3f, 0.8f,  // top right
	// 	  0.0f,  0.5f,  0.4f, 0.8f, 0.4f,  // bottom right
	// 	  0.5f, -0.5f,  0.7f, 0.6f, 0.8f,  // bottom left
	// };

	// float vertexData[] = {
	// 	 // position   // color
	// 	 0.5f,  0.5f,  0.2f, 0.3f, 0.8f,  // top right
	// 	 0.5f, -0.5f,  0.4f, 0.8f, 0.4f,  // bottom right
	// 	-0.5f, -0.5f,  0.7f, 0.6f, 0.8f,  // bottom left
	// 	-0.5f,  0.5f,  0.9f, 0.4f, 0.6f,  // top left
	// 	 0.5f,  0.5f,  0.2f, 0.3f, 0.8f,  // top right
	// 	-0.5f, -0.5f,  0.7f, 0.6f, 0.8f,  // bottom left
	// };

	// A bad idea because OpenGL works explicitly with raw array & size
	// std::vector<float> vertexData= {
	// 	 // position    // color
	// 	 -0.5f, -0.5f,  0.2f, 0.3f, 0.8f,  // top right
	// 	  0.0f,  0.5f,  0.4f, 0.8f, 0.4f,  // bottom right
	// 	  0.5f, -0.5f,  0.7f, 0.6f, 0.8f,  // bottom left
	// };

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
	std::vector<VertexAttrib> vertexAttribs = {
		VertexAttrib(2),  // no. GL_FLOATS
		VertexAttrib(3)   // no. GL_FLOATS
	};
	VertexArray vertexArray = VertexArray((void*)vertexData, 4 * (2+3) * sizeof(float), indices, 6, vertexAttribs);
	// VertexArray vertexArray = VertexArray(vertexData, vertexAttribs);

	// Shader
	Shader shader = Shader("shader/vertex.vs", "shader/fragment.fs");

	RenderLoop(window, vertexArray, shader);

	return 0;
}
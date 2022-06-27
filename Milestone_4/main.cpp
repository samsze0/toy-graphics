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
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdexcept>
#include "texture.h"


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

		float mixRatio = sin(timeValue * 2) / 2.0f + 0.5f;
		shader.SetUniform1f("mixRatio", mixRatio);

		float Opacity = sin(timeValue * 3) / 2.0f + 0.5f;
		shader.SetUniform1f("opacity", Opacity);

		shader.SetUniform1i("Texture1", 0);  // implicit ; default active texture unit is 0 hence its location is default
		shader.SetUniform1i("Texture2", 1);

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
	if (!glfwInit())
		throw std::runtime_error("GLFW: fail to initialise");

	// Version 4.1 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create window
	window = glfwCreateWindow(640, 640, "Toy OpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("GLFW: fail to create window");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("GLAD: fail to initialise");	

	// Vertex Data
	float vertexData[] = {
		 // position   // color           // texture coord
		 0.5f,  0.5f,  0.2f, 0.3f, 0.8f,  1.0f, 1.0f,  // top right
		 0.5f, -0.5f,  0.4f, 0.8f, 0.4f,  1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f,  0.7f, 0.6f, 0.8f,  0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f,  0.9f, 0.4f, 0.6f,  0.0f, 1.0f,  // top left
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
	vertexAttribVector.Push<float>(2, false);
	VertexArray vertexArray = VertexArray((void*)vertexData, 4 * vertexAttribVector.GetStride(), indices, 6, vertexAttribVector);

	// Shader
	Shader shader = Shader("shader/vertex.vs", "shader/fragment.fs");

	// Padding/alignment issue: OpenGL expects row of pixels to be padded to a multiple of 4 bytes
	// https://stackoverflow.com/questions/15983607/opengl-texture-tilted
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Texture
	Texture texture1("asset/opengl.png", 0);
	Texture texture2("asset/smile.png", 1);

	// Blending
	GLCheckError(glEnable(GL_BLEND));
	GLCheckError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	RenderLoop(window, vertexArray, shader);

	return 0;
}
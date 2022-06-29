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
// GLM: header-only maths lib ; OpenGL specific. Column-major ordering for matrices
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


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
		renderer.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		shader.use();
		vertexArray.bind();

		// Uniform (because some uniforms change with time hence place inside renderloop)
		float timeValue = glfwGetTime();

		float mixRatio = sin(timeValue * 2) / 2.0f + 0.5f;
		shader.SetUniform1f("mixRatio", mixRatio);

		float Opacity = sin(timeValue * 2) / 2.0f + 0.5f;
		shader.SetUniform1f("opacity", Opacity);

		// Model Transform
		// 4x4 identity matrix (diagonal values = 1)
		glm::mat4 Model = glm::mat4(1.0f);
		// Rotate matrix by z-axis
		// Model = glm::rotate(Model, glm::radians(sin(timeValue * 2) * 90), glm::vec3(0.0, 0.0, 1.0));
		// Rotate matrix by xy
		Model = glm::rotate(Model, glm::radians(timeValue*60), glm::vec3(1.0, 1.0, 1.0));
		// Scale matrix by 0.5 in all dimensions
		Model = glm::scale(Model, glm::vec3(0.5, 0.5, 0.5));
		// Translate matrix
		Model = glm::translate(Model, glm::vec3(sin(timeValue), cos(timeValue), 0.0f));
		shader.SetUniformMatrix4fv("Model", Model);

		// View Transform
		glm::mat4 View = glm::mat4(1.0f);
		// Simulate camera moving away (every object moving into -ve z)
		View = glm::translate(View, glm::vec3(0.0f, 0.0f, -timeValue/3));
		shader.SetUniformMatrix4fv("View", View);

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
	// Defining vertex position in world coord
	float vertexData[] = {
		// position           // texture coord
		// 1st face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		// 2nd face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		// 3rd face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		// 4th face
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 // 5th face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		// 6th face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	// VAO
	VertexAttribVector vertexAttribVector;
	vertexAttribVector.Push<float>(3, false);
	vertexAttribVector.Push<float>(2, false);
	VertexArray vertexArray = VertexArray((void*)vertexData, 6*6 * vertexAttribVector.GetStride(), vertexAttribVector);

	// Shader
	Shader shader = Shader("shader/vertex.vs", "shader/fragment.fs");

	// Padding/alignment issue: OpenGL expects row of pixels to be padded to a multiple of 4 bytes
	// https://stackoverflow.com/questions/15983607/opengl-texture-tilted
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Texture
	Texture texture1("asset/opengl.png", 0);
	Texture texture2("asset/smile.png", 1);

	shader.use();
	shader.SetUniform1i("Texture1", 0);  // implicit ; default active texture unit is 0 hence its location is default
	shader.SetUniform1i("Texture2", 1);

	// Blending
	GLCheckError(glEnable(GL_BLEND));
	// glBlendFunc(src, dest)
	// src: default is GL_ONE
	// dest: default is GL_ZERO
	// Apply blend func to all color channels (all of RGBA)
	GLCheckError(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	// Set blend mode: default is GL_FUNC_ADD
	GLCheckError(glBlendEquation(GL_FUNC_ADD));

	// Geometry Pipeline
	// Model-view-projection transformation matrix (for 2D just Model-view)

	// Projection
	// Orthogonal view volume: centered at 0 in world space, 4:3 aspect ratio
	// glm::ortho(L, R, T, B, Near, Far)
	// glm::mat4 projMat = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	glm::mat4 Projection;
	// glm::perspective(fov, aspect ratio, near, far)
	Projection = glm::perspective(glm::radians(60.0f), 640.0f / 640.0f, 0.1f, 100.0f);
	shader.use();
	shader.SetUniformMatrix4fv("Projection", Projection);

	// View & Model
	// Move over to render loop because we want animation

	// Enable Z-buffer depth-test
	GLCheckError(glEnable(GL_DEPTH_TEST));

	// Disable face culling
	// GLCheckError(glDisable(GL_CULL_FACE));

	RenderLoop(window, vertexArray, shader);

	return 0;
}
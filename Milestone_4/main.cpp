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
#include "camera.h"


static float window_width = 1280.0f;
static float window_height = 960.0f;

static double last_mouse_pos_x;
static double last_mouse_pos_y;

static bool first_mouse = true;

static float last_frame = 0.0f;

static Renderer renderer;
static Camera camera;

static void mouse_callback(GLFWwindow* window, double mouse_pos_x, double mouse_pos_y) {
	if (first_mouse) {
		last_mouse_pos_x = mouse_pos_x;
		last_mouse_pos_y = mouse_pos_y;
		first_mouse = false;
	}

	double x_offset = mouse_pos_x - last_mouse_pos_x;
	double y_offset = last_mouse_pos_y - mouse_pos_y;  // reversed: y ranges bottom to top

	camera.Look(x_offset, y_offset);

	last_mouse_pos_x = mouse_pos_x;
	last_mouse_pos_y = mouse_pos_y;
}


static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GLCheckError(glViewport(0, 0, width, height));
	window_width = width;
	window_height = height;
}

static void processInput(GLFWwindow* window, float deltaTime) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.MoveForward(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.MoveBack(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.MoveLeft(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.MoveRight(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.MoveUp(deltaTime);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		camera.MoveDown(deltaTime);
}

static void RenderLoop(GLFWwindow* window, VertexArray& vertexArray, Shader& shader) {
	while (!glfwWindowShouldClose(window)) {
		float current_frame = glfwGetTime();
		float deltaTime = current_frame - last_frame;
		// std::cout << "[Delta time (ms)] " << deltaTime << std::endl;
		// std::cout << "[Frame rate] " << 1 / (deltaTime*0.001) << std::endl;

		processInput(window, deltaTime);
		last_frame = current_frame;

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

		// Project Transform
		glm::mat4 Projection = camera.GetProjectionMatrix(window_width/window_height);
  	shader.SetUniformMatrix4fv("Projection", Projection);

		// View Transform
		// glm::mat4 View = glm::mat4(1.0f);
		// // Simulate camera moving away (every object moving into -ve z)
		// View = glm::translate(View, glm::vec3(0.0f, 0.0f, -timeValue/3));
		// shader.SetUniformMatrix4fv("View", View);
		// const float radius = 10.0f;
		// float camX = sin(glfwGetTime()) * radius;
		// float camZ = cos(glfwGetTime()) * radius;
		// glm::mat4 View;
		// // glm::lookAt(camera position, target position, up vector)
		// View = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 View = camera.GetViewMatrix();
		shader.SetUniformMatrix4fv("View", View);

		// Model Transform
		// // 4x4 identity matrix (diagonal values = 1)
		// glm::mat4 Model = glm::mat4(1.0f);
		// // Rotate matrix by z-axis
		// // Model = glm::rotate(Model, glm::radians(sin(timeValue * 2) * 90), glm::vec3(0.0, 0.0, 1.0));
		// // Rotate matrix by xy
		// Model = glm::rotate(Model, glm::radians(timeValue*60), glm::vec3(1.0, 1.0, 1.0));
		// // Scale matrix by 0.5 in all dimensions
		// Model = glm::scale(Model, glm::vec3(0.5, 0.5, 0.5));
		// // Translate matrix
		// Model = glm::translate(Model, glm::vec3(sin(timeValue), cos(timeValue), 0.0f));
		// shader.SetUniformMatrix4fv("Model", Model);

		glm::vec3 TranslationList[] = {
			glm::vec3( 0.0f,  0.0f,  0.0f),
			glm::vec3( 2.0f,  2.0f, -2.0f),
			glm::vec3(-2.0f, -2.0f, -2.0f),
			glm::vec3( 2.0f, -2.0f, -2.0f),
			glm::vec3(-2.0f,  2.0f, -2.0f),
			glm::vec3( 4.0f,  4.0f, -4.0f),
			glm::vec3(-4.0f, -4.0f, -4.0f),
			glm::vec3( 4.0f, -4.0f, -4.0f),
			glm::vec3(-4.0f,  4.0f, -4.0f),
			glm::vec3( 2.0f,  2.0f,  2.0f),
			glm::vec3(-2.0f, -2.0f,  2.0f),
			glm::vec3( 2.0f, -2.0f,  2.0f),
			glm::vec3(-2.0f,  2.0f,  2.0f),
			glm::vec3( 4.0f,  4.0f,  4.0f),
			glm::vec3(-4.0f, -4.0f,  4.0f),
			glm::vec3( 4.0f, -4.0f,  4.0f),
			glm::vec3(-4.0f,  4.0f,  4.0f),
		};

		for (const glm::vec3& translation : TranslationList) {
			glm::mat4 Model = glm::mat4(1.0f);
			Model = glm::translate(Model, translation);
			Model = glm::rotate(Model, glm::radians(timeValue*30), glm::vec3(1.0f, 1.0f, 1.0f));
			shader.SetUniformMatrix4fv("Model", Model);
			renderer.Draw(vertexArray, shader);
		}

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
	window = glfwCreateWindow(window_width, window_height, "Toy OpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("GLFW: fail to create window");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Capture mouse cursor: hide cursor and keep it stays at center of window
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("GLAD: fail to initialise");	

	// Renderer
	renderer.EnableDepthTest();
	// renderer.EnableFaceCulling();

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

	// Projection & View Transform
	// Move over to Camera class

	// Model Transform
	// Move over to render loop because we want animation

	RenderLoop(window, vertexArray, shader);

	return 0;
}
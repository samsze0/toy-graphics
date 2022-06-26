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


struct Image {
	int width;
	int height;
	unsigned char* data;
};


static Image* LoadImage(const std::string& filename) {
	int width, height, BPP;
	stbi_set_flip_vertically_on_load(true);
	// Fill width, height, & bit-per-pixel. No. color channels
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &BPP, 3);
	if (data == nullptr)
		throw std::runtime_error("Fail to load image file " + filename);
	Image* image = new Image({width, height, data});
	return image;
}

static unsigned int GenAndBindTexture(unsigned int slot) {
	unsigned int ID;
	GLCheckError(glGenTextures(1, &ID));
	GLCheckError(glActiveTexture(GL_TEXTURE0 + slot));  // implicit ; GL_TEXTURE0 is activated by default
																							 				// texture unit - "slot" of texture
																											// "slots" enum are consecutive
	GLCheckError(glBindTexture(GL_TEXTURE_2D, ID));     // bind to the active texture unit

	// set the texture wrapping/filtering options (on currently bound texture)
	GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	// With mipmap
	// GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
	// GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
	// GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
	// GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
 	GLCheckError(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	return ID;
}

static void LoadImageToTexture(Image* image) {
	// Texture target ; Mipmap level ; Storage format of texture ; width & height of texture ; 0 ; Source image format ; Image data
	GLCheckError(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data));
	GLCheckError(glGenerateMipmap(GL_TEXTURE_2D));  // Optional. Automatically generate all mipmaps
	stbi_image_free(image->data);  // Ownership problem: not a good idea to free memory in somewhere different from where it is allocated
	delete image;
}


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

	Image* image1 = LoadImage("asset/opengl.png");
	unsigned int texture1ID = GenAndBindTexture(0);
	LoadImageToTexture(image1);

	Image* image2 = LoadImage("asset/smile.png");
	unsigned int texture2ID = GenAndBindTexture(1);
	LoadImageToTexture(image2);

	RenderLoop(window, vertexArray, shader);

	return 0;
}
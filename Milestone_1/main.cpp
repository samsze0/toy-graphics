#include <iostream>
// #include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


static unsigned int CompileShader(unsigned int type, const std::string& shaderSource) {
	unsigned int shaderObj = glCreateShader(type);
	const char* shaderSource_cstr = shaderSource.c_str();

	// ID; no. strings; shader source; null
	glShaderSource(shaderObj, 1, &shaderSource_cstr, nullptr);
	glCompileShader(shaderObj);

	int success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		glDeleteShader(shaderObj);
		return -1;
	}

	return shaderObj;
}

static unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	unsigned int shaderProgram = glCreateProgram();
	unsigned int vertexShaderObj = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShaderObj = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(shaderProgram, vertexShaderObj);
	glAttachShader(shaderProgram, fragmentShaderObj);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	// Delete shader objects after link
	glDeleteShader(vertexShaderObj);
	glDeleteShader(fragmentShaderObj);

	return shaderProgram;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "Window resized" << std::endl;
}

static void processInput(GLFWwindow *window) {
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

static void RenderLoop(GLFWwindow* window) {
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// Clear color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// With VBO (drawing a triangle)
		// Draw mode; starting index of array; no. verticies
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

	// Initialise GLEW
	// if (GLEW_OK != glewInit())
	// 	std::cout << "Error" << std::endl;

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl
;		return -1;
	}

	float vertexData[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f,
	};

	// VAO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexData, GL_STATIC_DRAW);

	// 0th vertex attrib; 2 GL_FLOAT; not normalised; stride; no offset (require weird cast)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Shader
	std::string vertexShaderSource = R"glsl(
		#version 410 core

		layout(location = 0) in vec2 position;

		void main() {
		  gl_Position.xy = position;
		  gl_Position.z = 0.0;
		  gl_Position.w = 1.0;
		}
	)glsl";
	std::string fragmentShaderSource = R"glsl(
		#version 410 core

		out vec4 color;

		void main() {
		  color = vec4(0.5, 0.7, 0.5, 1.0);
		}
	)glsl";
	unsigned int shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

	glUseProgram(shaderProgram); 
	glBindVertexArray(VAO);

	RenderLoop(window);

	return 0;
}
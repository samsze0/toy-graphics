#include "pch.h"
#include "shader.h"
#include "error.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vertexAttribVector.h"
#include "renderer.h"
#include "texture.h"
#include "camera.h"
#include "ui/demo.h"
#include "ui/menu.h"
#include "ui/stats.h"
#include "model/vertexData.h"
#include "model/translationList.h"


// States & constants as static variables

// GL 4.1 + GLSL 150
static const char* glsl_version = "#version 150";

static float window_width = 640.0f;
static float window_height = 640.0f;

static double last_mouse_pos_x;
static double last_mouse_pos_y;

static bool first_mouse = true;

static float last_frame = 0.0f;
static float deltaTime;

static GLFWwindow* window = nullptr;
// TODO: Optional type and initialise with null. Init all of them in a single Init() function
static Renderer renderer;
static Camera camera;
static Logger logger("main");

static bool show_menu = false;
static bool show_stats = true;

static ImVec4 clear_color = ImVec4(75.0f/256.0f, 114.0f/256.0f, 154.0f/256.0f, 1.00f);

static void viewport_mouse_callback(GLFWwindow* window, double mouse_pos_x, double mouse_pos_y) {
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

// See
// https://stackoverflow.com/questions/71680516/how-do-i-handle-mouse-events-in-general-in-imgui-with-glfw
// https://github.com/ocornut/imgui/blob/master/docs/FAQ.md#q-how-can-i-tell-whether-to-dispatch-mousekeyboard-to-dear-imgui-or-my-application
static void mouse_pos_callback(GLFWwindow* window, double mouse_pos_x, double mouse_pos_y) {
  // (1) ALWAYS forward mouse data to ImGui! This is automatic with default backends. With your own backend:
  ImGuiIO& io = ImGui::GetIO();
  io.AddMousePosEvent(mouse_pos_x, mouse_pos_y);

  // (2) ONLY forward mouse data to your underlying app/game.
  // if (!io.WantCaptureMouse)
    // mouse_callback(window, mouse_pos_x, mouse_pos_y);
  if (!show_menu)
  	viewport_mouse_callback(window, mouse_pos_x, mouse_pos_y);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GLCheckError(glViewport(0, 0, width, height));
	window_width = width;
	window_height = height;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Cause stutter because it is asynchronous?
	// if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	// 	camera.MoveForward(deltaTime);

	// Doesn't work with imgui because GLFW_CURSOR_DISABLED and glfwSetCursorPosCallback messes up the cursor
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		if (show_menu) {
			first_mouse = true;
			// Capture mouse cursor: hide cursor and keep it stays at center of window
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		} else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		show_menu = !show_menu;
	}
}

static void processPlayerMovementInput(GLFWwindow* window) {
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

static void RenderLoop(VertexArray& vertexArray, Shader& shader) {
	while (!glfwWindowShouldClose(window)) {
		float current_frame = glfwGetTime();
		deltaTime = (current_frame - last_frame) * 1000;
		// std::cout << "[Delta time (ms)] " << deltaTime << std::endl;
		// std::cout << "[Frame rate] " << 1 / (deltaTime*0.001) << std::endl;
		WARN(logger, "[Delta time (ms)] {0}", deltaTime);

		// Process events e.g. keyboard
		glfwPollEvents();
		if (!show_menu)
			processPlayerMovementInput(window);

		last_frame = current_frame;

		// Clear color buffer
		renderer.Clear(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		// renderer.Clear(1.0f, 1.0f, 1.0f, 1.0f);

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
		glm::mat4 View = camera.GetViewMatrix();
		shader.SetUniformMatrix4fv("View", View);

		// Model Transform
		for (const glm::vec3& translation : TranslationList) {
			glm::mat4 Model = glm::mat4(1.0f);
			Model = glm::translate(Model, translation);
			Model = glm::rotate(Model, glm::radians(timeValue*30), glm::vec3(1.0f, 1.0f, 1.0f));
			shader.SetUniformMatrix4fv("Model", Model);
			renderer.Draw(vertexArray, shader);
		}

		// Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

   	// UI::Demo(show_menu);
   	UI::Menu(show_menu, show_stats, camera, clear_color, window_width, window_height);
   	UI::Stats(show_stats, deltaTime, window_width, window_height, last_mouse_pos_x, last_mouse_pos_y);

    // Imgui Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Double buffering
		glfwSwapBuffers(window);
	}

	// Imgui cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

	glfwTerminate();
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
		throw std::runtime_error("GLFW: fail to initialise");

	// Version 4.1 core
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Other window hints
	// glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	// glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);  // "Decorated": border, close widget, title bar
	glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
	// glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);  // Enable transparency

	// OSX specific window hints
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);

	// Window icon
	// GLFWimage images[2];
	// images[0] = load_icon("my_icon.png");
	// images[1] = load_icon("my_icon_small.png");
	// glfwSetWindowIcon(window, 2, images);

	// Create window
	window = glfwCreateWindow(window_width, window_height, "Toy OpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		throw std::runtime_error("GLFW: fail to create window");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glfwSwapInterval(1); // Enable vsync

	glfwSetCursorPosCallback(window, mouse_pos_callback);

	// Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup UI font
  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  io.Fonts->AddFontFromFileTTF("./asset/Roboto-Medium.ttf", 16.0f);

	// Initialise GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("GLAD: fail to initialise");	

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, key_callback);

	// Renderer
	renderer.Init();
	renderer.EnableDepthTest();
	// renderer.EnableFaceCulling();
	// renderer.EnableBlending();

	// VAO
	VertexAttribVector vertexAttribVector;
	vertexAttribVector.Push<float>(3, false);
	vertexAttribVector.Push<float>(2, false);
	VertexArray vertexArray = VertexArray((void*)vertexData, 6*6 * vertexAttribVector.GetStride(), vertexAttribVector);

	// Shader
	Shader shader = Shader("shader/vertex.vs", "shader/fragment.fs");

	// Texture
	Texture texture1("asset/opengl.png", 0);
	Texture texture2("asset/smile.png", 1);

	shader.use();
	shader.SetUniform1i("Texture1", 0);  // implicit ; default active texture unit is 0 hence its location is default
	shader.SetUniform1i("Texture2", 1);

	RenderLoop(vertexArray, shader);

	return 0;
}
#include "window.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

Window::Window(int width, int height, std::string title) {
	spdlog::trace("Window::Window({}, {}, \"{}\")", title, width, height);

	glfwSetErrorCallback([](int error, const char* description) {
		spdlog::error("GLFW error: {}", description);
	});

	// GLFW initialization
	if (!glfwInit()) {
		spdlog::error("Failed to initialize GLFW");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	if (width <= 0 || height <= 0) {
		spdlog::error("Invalid window size");
		exit(EXIT_FAILURE);
	}

	if (title.empty()) {
		spdlog::error("Invalid window title");
		exit(EXIT_FAILURE);
	}

	if (window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); !window) {
		spdlog::error("Failed to create window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	// GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::error("Failed to initialize GLAD");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// OpenGL configuration
	glViewport(0, 0, width, height);

	// ImGui initialization
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Window::render(std::function<void(GLFWwindow*)> render) {
	spdlog::trace("Window::render({})", (void*)(&render));
	m_render = render;
}

void Window::update(std::function<void(GLFWwindow*)> update) {
	spdlog::trace("Window::update({})", (void*)(&update));
	m_update = update;
}

void Window::run() {
	spdlog::trace("Window::run()");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (m_update) {
			m_update(window);
		}

		if (m_render) {
			m_render(window);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

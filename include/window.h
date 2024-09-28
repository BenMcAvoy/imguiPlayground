#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <functional>

class Window {
public:
	Window(int width, int height, std::string title);

	void render(std::function<void(GLFWwindow*)> render);
	void update(std::function<void(GLFWwindow*)> update);

	void run();

	GLFWwindow* window;

private:
	std::function<void(GLFWwindow*)> m_render;
	std::function<void(GLFWwindow*)> m_update;
};

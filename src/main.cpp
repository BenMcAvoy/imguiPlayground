#include "dockspace.h"
#include "window.h"

#include <imgui/imgui.h>
#include <spdlog/spdlog.h>

int main(void) {
	spdlog::set_level(spdlog::level::trace);

	Window window(800, 600, "imguiPlayground");

	window.render([](GLFWwindow* window) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Exit")) {
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		dockspace();

		ImGui::Begin("imguiPlayground");

		static bool demo = false;
		if (ImGui::Button("Demo Window")) {
			demo = !demo;
		}

		ImGui::End();

		if (demo) ImGui::ShowDemoWindow(&demo);
	});

	window.run();
}

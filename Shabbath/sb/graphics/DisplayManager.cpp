#include "DisplayManager.hpp"

SB_MODULE(graphics)

GLFWwindow* DisplayManager::window = nullptr;

void DisplayManager::CreateDisplay()
{

	if (!glfwInit()) {
		return;
	}

	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (!glewInit()) {
		return;
	}
}

void DisplayManager::UpdateDisplay()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool DisplayManager::ShouldClose()
{
	return glfwWindowShouldClose(window);
}


SB_MODULE_END
#include "DisplayManager.hpp"

SB_MODULE(graphics)

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
#pragma once

#include "../Common.hpp"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

SB_MODULE(graphics)

class DisplayManager {
private:
	static GLFWwindow* window;

public:
	static void CreateDisplay();
	static void UpdateDisplay();
	static bool ShouldClose();

};

SB_MODULE_END
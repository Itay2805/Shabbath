#pragma once

#include "../Common.hpp"

SB_MODULE(graphics)

class DisplayManager {
private:
	static GLFWwindow* window;

public:
	static void CreateDisplay();
	static void UpdateDisplay();
	static bool ShouldClose();

private:
	static void _stdcall glDebugCall(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	static void glfwErrorCall(int id, const char * message);

};

SB_MODULE_END
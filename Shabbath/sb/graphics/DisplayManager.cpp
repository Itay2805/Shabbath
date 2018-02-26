#include "DisplayManager.hpp"

SB_MODULE(graphics)

GLFWwindow* DisplayManager::window = nullptr;

void DisplayManager::CreateDisplay()
{

	glfwSetErrorCallback(DisplayManager::glfwErrorCall);

	if (!glfwInit()) {
		return;
	}

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	
	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (!glewInit()) {
		return;
	}

	glDebugMessageCallback(DisplayManager::glDebugCall, nullptr);
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

void _stdcall DisplayManager::glDebugCall(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam)
{
	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW: 
		std::cout << "[OpenGL/Warning] " << message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		std::cout << "[OpenGL/Error] " << message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		std::cout << "[OpenGL/Fatal] " << message << std::endl;
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: 
		std::cout << "[OpenGL/Notification] " << message << std::endl;
		break;
	default:
		std::cout << "[OpenGL] " << message << std::endl;
	}

}

void DisplayManager::glfwErrorCall(int id, const char * message)
{
	std::cout << "[GLFW/Error] " << message << std::endl;
}


SB_MODULE_END
#include "DisplayManager.hpp"

SB_MODULE(graphics)

GLFWwindow* DisplayManager::window = nullptr;

void DisplayManager::CreateDisplay()
{

	glfwSetErrorCallback(DisplayManager::glfwErrorCall);

	if (!glfwInit()) {
		std::cout << "Error initializing glfw!" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	
	window = glfwCreateWindow(960, 540, "Shabbath", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		std::cout << "Error creating glfw!" << std::endl;
		return;
	}

	glfwMakeContextCurrent(window);

	// TODO: Error logging
	if (glewInit() != GLEW_NO_ERROR) {
		std::cout << "Error initializing glew!" << std::endl;
		return;
	}

	std::cout << "OpenGL Loaded:" << std::endl;
	std::cout << "\tVendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "\tRenderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "\tVersion: " << glGetString(GL_VERSION) << std::endl;

#ifdef SB_DEBUG
	std::cout << "Enabling OpenGL debbuging" << std::endl;

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(DisplayManager::glDebugCall, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
#endif // SB_DEBUG

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
	std::string sourceStr, severtityStr, typeStr;

	switch (severity) {
	case GL_DEBUG_SEVERITY_LOW: 
		severtityStr = "Low";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		severtityStr = "Medium";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		severtityStr = "High";
		break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: 
		severtityStr = "Notification";
	}

	switch (source) {
	case GL_DEBUG_SOURCE_API:
		sourceStr = "API";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		sourceStr = "Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		sourceStr = "Other";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		sourceStr = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		sourceStr = "Third Party";
		break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		sourceStr = "Window System";
		break;
	}

	switch (type) {
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		typeStr = "Debrecated Behavior";
		break;
	case GL_DEBUG_TYPE_ERROR:
		typeStr = "Error";
		break;
	case GL_DEBUG_TYPE_MARKER:
		typeStr = "Marker";
		break;
	case GL_DEBUG_TYPE_OTHER:
		typeStr = "Other";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		typeStr = "Performance";
		break;
	case GL_DEBUG_TYPE_POP_GROUP:
		typeStr = "Pop Group";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		typeStr = "Portability";
		break;
	case GL_DEBUG_TYPE_PUSH_GROUP:
		typeStr = "Push Group";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		typeStr = "Undefined Behavior";
		break;
	}

	std::cout << "[OpenGL/" << typeStr << "-" << severtityStr << "] from " << sourceStr << " -> " << message << std::endl;

}

void DisplayManager::glfwErrorCall(int id, const char * message)
{
	std::cout << "[GLFW/Error] " << message << std::endl;
}


SB_MODULE_END
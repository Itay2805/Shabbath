#include "graphics\DisplayManager.hpp"

int main() {
	using namespace sb::graphics;

	DisplayManager::CreateDisplay();
	while (!DisplayManager::ShouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		DisplayManager::UpdateDisplay();
	}
}
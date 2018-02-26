#include "graphics\DisplayManager.hpp"

int main() {
	using namespace sb::graphics;

	DisplayManager::CreateDisplay();
	while (!DisplayManager::ShouldClose()) {
		DisplayManager::UpdateDisplay();
	}
}
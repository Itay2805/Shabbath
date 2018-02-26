#include "graphics\DisplayManager.hpp"
#include "graphics\gl\Texture.hpp"

int main() {
	using namespace sb::graphics;
	using namespace sb::graphics::gl;

	DisplayManager::CreateDisplay();
	
	Texture texture(1024, 1024);

	while (!DisplayManager::ShouldClose()) {
		DisplayManager::UpdateDisplay();
	}
}
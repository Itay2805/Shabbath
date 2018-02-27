#include "graphics\DisplayManager.hpp"
#include "graphics\gl\Texture.hpp"
#include "graphics\gl\ShaderProgram.hpp"
#include "graphics\gl\VertexArray.hpp"

#include "graphics\AnimatedSprite.hpp"

int main() {
	using namespace sb::graphics;
	using namespace sb::graphics::gl;

	DisplayManager::CreateDisplay();
	
	AnimatedSprite sprite(1024, 1024);

	GLuint* image_data = new GLuint[1024 * 1024];
	for (int i = 0; i<1024 * 1024; i++) {
		image_data[i] = rand();
	}
	sprite.UpdateTexture(image_data);

	VertexArray arr;

	GLfloat data[12] = {
		-1.0,-1.0, -1.0, 1.0, 1.0,-1.0,
		1.0,-1.0, 1.0, 1.0, -1.0, 1.0,
	};
	Buffer buf(data, sizeof(data));
	buf.Push<float>(2);
	arr.AddBuffer(buf);

	ShaderProgram program("TextureCopy");
	program.AttachShader(GL_VERTEX_SHADER, R"(
#version 450 core
layout(location = 0) in vec2 coord;
out vec2 uvCoord;
void main(void) {
	gl_Position = vec4(coord, 0.0, 1.0);
	uvCoord = coord;
}
)");

	program.AttachShader(GL_FRAGMENT_SHADER, R"(
#version 450 core
uniform sampler2D tex;
in vec2 uvCoord;
layout(location = 0) out vec4 color;
void main(void) {
	color = texture2D(tex, uvCoord);
}
)");

	if (!program.Link()) {
		system("PAUSE");
		return 0;
	}

	int tick = 0;
	float avgTransferTime = 0;

	while (!DisplayManager::ShouldClose()) {
		DisplayManager::ClearDisplay();

		for (int i = 0; i<1024 * 1024; i++) {
			image_data[i] = rand();
		}
		double time = glfwGetTime();
		sprite.UpdateTexture(image_data);
		double took = glfwGetTime() - time;
		avgTransferTime += took;

		if (tick % 60 == 0) {
			std::cout << "[Debug] Transfer and update time: " << avgTransferTime / 60.0f << std::endl;
			avgTransferTime = 0;
		}


		program.Bind();
		sprite.BindTexture();
		// glUniform1i(0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 8);

		DisplayManager::UpdateDisplay();
		tick++;
	}

	DisplayManager::CloseDisplay();

	system("PAUSE");
}
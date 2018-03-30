#include "graphics\DisplayManager.hpp"
#include "graphics\gl\Texture.hpp"
#include "graphics\gl\ShaderProgram.hpp"
#include "graphics\gl\VertexArray.hpp"

#include "graphics\AnimatedSprite.hpp"

#include "memory\MemoryManager.h"

int main() {
	using namespace sb::graphics;
	using namespace sb::graphics::gl;

	DisplayManager::CreateDisplay();
	
	AnimatedSprite sprite(1024, 1024, ASStreamingMode::DOUBLE_PBO);

	GLuint* image_data = MemoryManager::Get()->AllocateStatic<GLuint>(1024 * 1024);
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
	vec2 c = vec2(0.0, 0.0);
	if(coord.x > 0.0) {
		c.x = 1.0;
	}
	if(coord.y > 0.0) {
		c.y = 1.0;
	}
	uvCoord = c;
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

	ASStreamingMode mode = ASStreamingMode::DOUBLE_PBO;

	std::cout << "[DOUBLE_PBO] Starting PBO benchmark " << std::endl;
	
	while (!DisplayManager::ShouldClose()) {
		DisplayManager::ClearDisplay();

		for (int i = 0; i<1024 * 1024; i++) {
			image_data[i] = rand();
		}
		double time = glfwGetTime();
		sprite.UpdateTexture(image_data);
		double took = glfwGetTime() - time;
		avgTransferTime += took;

		if (tick % (60 * 60) == 0 && tick != 0) {
			if (mode == ASStreamingMode::DOUBLE_PBO) {
				std::cout << "[DOUBLE_PBO] Transfer and update time: " << avgTransferTime / (60.0f * 60.0f) << std::endl;
				mode = ASStreamingMode::MAPPING;
				sprite.UpdateStreamingMode(mode);
			}
			else if (mode == ASStreamingMode::MAPPING) {
				std::cout << "[MAPPING] Transfer and update time: " << avgTransferTime / (60.0f * 60.0f) << std::endl;
				mode = ASStreamingMode::PBO;
				sprite.UpdateStreamingMode(mode);
			}
			else if (mode == ASStreamingMode::PBO) {
				std::cout << "[PBO] Transfer and update time: " << avgTransferTime / (60.0f * 60.0f) << std::endl;
				mode = (ASStreamingMode)-1;
			}
			else {
				std::cout << "[Debug] Done";
				DisplayManager::CloseDisplay();
			}
			avgTransferTime = 0;
		}

		program.Bind();
		sprite.BindTexture();
		// glUniform1i(0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 8);

		DisplayManager::UpdateDisplay();
		tick++;
	}

	system("PAUSE");
}
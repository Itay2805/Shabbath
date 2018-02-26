#include "graphics\DisplayManager.hpp"
#include "graphics\gl\Texture.hpp"
#include "graphics\gl\ShaderProgram.hpp"
#include "graphics\gl\VertexArray.hpp"

int main() {
	using namespace sb::graphics;
	using namespace sb::graphics::gl;

	DisplayManager::CreateDisplay();
	
	Texture texture;

	GLuint* image_data = new GLuint[960 * 540];
	for (int i = 0; i<960 * 540; i++) {
		image_data[i] = rand();
	}
	texture.LoadData(960, 540, image_data);
	delete[] image_data;

	VertexArray arr;

	GLfloat data[8] = {
		-1,-1, -1, 1,
		1,-1,  1, 1,
	};
	Buffer buf(data, sizeof(data));
	buf.Push<float>(2);
	arr.AddBuffer(buf);

	ShaderProgram program("TextureCopy");
	program.AttachShader(GL_VERTEX_SHADER, R"(
#version 450 core
layout(location = 0) in vec2 coord;
void main(void) {
	gl_Position = vec4(coord, 0.0, 1.0);
}
)");

	program.AttachShader(GL_FRAGMENT_SHADER, R"(
#version 450 core
readonly restrict uniform layout(rgba8) image2D image;
layout(location = 0) out vec4 color;
void main(void) {
	color = imageLoad(image, ivec4(gl_FragCoord).xy);
}
)");

	program.Link();

	while (!DisplayManager::ShouldClose()) {
		
		program.Bind();
		texture.Bind();
		glUniform1i(0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 4);

		DisplayManager::UpdateDisplay();
	}
}
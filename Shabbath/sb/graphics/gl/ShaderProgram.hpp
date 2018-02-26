#pragma once

#include "../../Common.hpp"

SB_SUBMODULE(graphics, gl)

class ShaderProgram {
private:
	GLuint program;


public:
	ShaderProgram(std::string name = "<unnamed>");

	void AttachShader(GLenum type, std::string code);

	bool Link();

	void Bind();

	inline GLuint GetProgram() const { return program; }
};

SB_SUBMODULE_END
#include "ShaderProgram.hpp"
SB_SUBMODULE(graphics, gl)

ShaderProgram::ShaderProgram(std::string name)
{
	program = glCreateProgram();
	glObjectLabel(GL_PROGRAM, program, -1, name.c_str());
}

void ShaderProgram::AttachShader(GLenum type, std::string code)
{
	GLuint shader = glCreateShader(type);
	const char* cstr = code.c_str();
	glShaderSource(shader, 1, &cstr, NULL);
	glCompileShader(shader);
	glAttachShader(program, shader);
	glDeleteShader(shader);
}

bool ShaderProgram::Link()
{
	glLinkProgram(program);
	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result != GL_TRUE) {
		char msg[10240];
		glGetProgramInfoLog(program, 10240, NULL, msg);
		std::cout << "Linking program failed:" << std::endl << msg << std::endl;
		return false;
	}
	return true;
}

void ShaderProgram::Bind()
{
	glUseProgram(program);
}

SB_SUBMODULE_END
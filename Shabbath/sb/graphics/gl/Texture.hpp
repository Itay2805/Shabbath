#pragma once

#include "../../Common.hpp"

SB_SUBMODULE(graphics, gl)

class Texture {
private:
	GLuint texture;
	GLenum type;
	int width, height;

public:
	Texture(GLenum type = GL_TEXTURE_2D, int storagewidth = 1024, int storageheight = 1024);
	Texture(int storagewidth, int storageheight);
	~Texture();

	void LoadData(int width, int height, void* data, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE);
	
	static Texture LoadFromFile(std::string path);

};

SB_SUBMODULE_END
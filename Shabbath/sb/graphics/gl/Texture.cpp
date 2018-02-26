#include "Texture.hpp"

SB_SUBMODULE(graphics, gl)

Texture::Texture(size_t storagewidth, size_t storageheight, GLenum type)
{
	glCreateTextures(type, 1, &texture);
	glTextureStorage2D(texture, 1, GL_RGBA8, storagewidth, storageheight);
}

Texture::Texture()
	: Texture(1024, 1024)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::LoadData(size_t width, size_t height, void * data, GLenum format, GLenum type)
{
	this->width = width;
	this->height = height;
	glTextureSubImage2D(texture, 0, 0, 0, width, height, format, type, data);
}

SB_SUBMODULE_END


#include "Texture.hpp"

SB_SUBMODULE(graphics, gl)

Texture::Texture(GLenum type, int storagewidth, int storageheight)
	: type(type)
{
	glCreateTextures(type, 1, &texture);
	glTextureStorage2D(texture, 1, GL_RGBA8, storagewidth, storageheight);
}

Texture::Texture(int storagewidth, int storageheight)
	: Texture(GL_TEXTURE_2D, storagewidth, storageheight)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::LoadData(int width, int height, void * data, GLenum format, GLenum type)
{
	this->width = width;
	this->height = height;
	glTextureSubImage2D(texture, 0, 0, 0, width, height, format, type, data);
}

SB_SUBMODULE_END


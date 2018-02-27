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
	Bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Texture::Bind() const
{
	glBindImageTexture(0, texture, 0, false, 0, GL_READ_ONLY, GL_RGBA8);
}

SB_SUBMODULE_END


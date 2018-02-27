#pragma once

#include "../../Common.hpp"

SB_SUBMODULE(graphics, gl)

class Texture {
private:
	GLuint texture;
	GLenum type;
	size_t width, height;

public:
	Texture(size_t storagewidth, size_t storageheight, GLenum type = GL_TEXTURE_2D);
	Texture();
	~Texture();

	void LoadData(size_t width, size_t height, void* data, GLenum format = GL_RGBA, GLenum type = GL_UNSIGNED_BYTE);
	
	void Bind() const;

	static Texture LoadFromFile(std::string path);

	inline size_t GetWidth() const { return width; }
	inline size_t GetHeight() const { return height; }
	inline GLenum GetType() const { return type; }
};

SB_SUBMODULE_END
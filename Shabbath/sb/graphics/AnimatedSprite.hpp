#pragma once

#include "../Common.hpp"

SB_MODULE(graphics) 

enum class ASStreamingMode {
	MAPPING,
	PBO,
	DOUBLE_PBO
};

class AnimatedSprite {
private:
	GLuint pbos[2];
	GLuint texture;
	GLubyte* imageData = 0;
	ASStreamingMode mode;
	size_t width, height;

	int index = 0;

public:
	AnimatedSprite(size_t width, size_t height, ASStreamingMode mode = ASStreamingMode::MAPPING);
	~AnimatedSprite();

	void UpdateTexture(const void* imageData);
	void BindTexture();

private:

};

SB_MODULE_END
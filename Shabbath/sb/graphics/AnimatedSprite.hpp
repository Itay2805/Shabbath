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
	ASStreamingMode mode;
	size_t width, height;

	int index = 0;

public:
	AnimatedSprite(size_t width, size_t height, ASStreamingMode mode = ASStreamingMode::DOUBLE_PBO);
	~AnimatedSprite();

	void UpdateTexture(const void* imageData);
	void BindTexture();

	void UpdateStreamingMode(ASStreamingMode mode);

private:

};

SB_MODULE_END
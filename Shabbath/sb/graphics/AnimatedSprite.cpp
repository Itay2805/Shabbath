#include "AnimatedSprite.hpp"

SB_MODULE(graphics)

AnimatedSprite::AnimatedSprite(size_t width, size_t height, ASStreamingMode mode)
	: width(width), height(height), mode(mode)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (mode != ASStreamingMode::MAPPING) {
		if (mode == ASStreamingMode::DOUBLE_PBO) {
			glGenBuffers(2, pbos);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbos[0]);
			glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, nullptr, GL_STREAM_DRAW);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbos[1]);
			glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, nullptr, GL_STREAM_DRAW);
		}else if(mode == ASStreamingMode::PBO) {
			glGenBuffers(1, pbos);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbos[0]);
			glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, nullptr, GL_STREAM_DRAW);
		}
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
}

AnimatedSprite::~AnimatedSprite()
{
	if (mode != ASStreamingMode::MAPPING) {
		if (mode == ASStreamingMode::DOUBLE_PBO) {
			glDeleteBuffers(2, pbos);
		}
		else if (mode == ASStreamingMode::PBO) {
			glDeleteBuffers(1, pbos);
		}
	}
	glDeleteTextures(1, &texture);
}

void AnimatedSprite::UpdateTexture(const void * imageData)
{
	int nextIndex = 0;
	if (mode != ASStreamingMode::MAPPING) {
		if (mode == ASStreamingMode::PBO) {
			index = nextIndex = 0;
		}
		else if (mode == ASStreamingMode::DOUBLE_PBO) {
			index = (index + 1) % 2;
			nextIndex = (index + 1) % 2;
		}

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbos[index]);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbos[nextIndex]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, imageData, GL_STREAM_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	}
}

void AnimatedSprite::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}



SB_MODULE_END

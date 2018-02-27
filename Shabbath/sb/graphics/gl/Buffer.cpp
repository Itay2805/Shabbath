#include "Buffer.hpp"

SB_SUBMODULE(graphics, gl)

Buffer::Buffer(const void* data, size_t size)
	: size(size)
{
	glCreateBuffers(1, &buffer);
	glNamedBufferStorage(buffer, size, data, 0);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &buffer);
}

void Buffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

SB_SUBMODULE_END


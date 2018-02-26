#pragma once

#include "../../Common.hpp"

SB_SUBMODULE(graphics, gl)

struct BufferElement {
	GLenum type;
	int count;
	GLboolean normalized;
	size_t size;
};

class Buffer {
private:
	std::vector<BufferElement> elements;

	GLuint buffer;
	size_t size;
	size_t stride;

public:
	Buffer(void* data, size_t size);
	~Buffer();

	template<typename A>
	void Push(int count) {
		std::cout << "Invalid type!" << std::endl;
	}

	template<>
	void Push<float>(int count) {
		elements.push_back({ GL_FLOAT, count, false, sizeof(GLfloat) });
		stride += sizeof(GLfloat) * count;
	}

	template<>
	void Push<unsigned int>(int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, false, sizeof(GLuint) });
		stride += sizeof(GLuint) * count;
	}
	
	template<>
	void Push<unsigned char>(int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, true, sizeof(GLubyte) });
		stride += sizeof(GLubyte) * count;
	}

	void Bind();

	inline GLuint GetBuffer() const { return buffer; }
	inline const std::vector<BufferElement>& GetElements() const { return elements; }
	inline size_t GetStride() const { return stride; }
	inline size_t GetSize() const { return size; }
};

SB_SUBMODULE_END
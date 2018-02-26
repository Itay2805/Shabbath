#pragma once

#include "../../Common.hpp"

#include "Buffer.hpp"

SB_SUBMODULE(graphics, gl)

class VertexArray {
private:
	GLuint array;

public:
	VertexArray();
	~VertexArray();

	void Bind() const;

	void AddBuffer(const Buffer& vb, int index = 0);

};

SB_SUBMODULE_END
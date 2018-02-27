#pragma once

#include "../Common.hpp"

SB_MODULE(graphics)

struct VertexData {
	GLfloat x, y;
	GLfloat u, v;
	GLuint tid;
};

class Renderable {
public:
	virtual GLuint GetTexture() const = 0;
};

class BatchRenderer {

};

SB_MODULE_END
#include "VertexArray.hpp"
SB_SUBMODULE(graphics, gl)

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &array);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &array);
}

void VertexArray::Bind() const
{
	glBindVertexArray(array);
}

void VertexArray::AddBuffer(const Buffer & buffer, int index)
{
	glVertexArrayVertexBuffer(array, index, buffer.GetBuffer(), 0, static_cast<GLsizei>(buffer.GetStride()));
	int attrib = 0;
	size_t offset = 0;
	for (auto element = buffer.GetElements().begin(); element < buffer.GetElements().end(); ++element) {
		glEnableVertexArrayAttrib(array, attrib);
		glVertexArrayAttribFormat(array, attrib, element->count, element->type, element->normalized, static_cast<GLsizei>(offset));
		glVertexArrayAttribBinding(array, attrib, index);
		offset += element->type;
		attrib++;
	}
}

SB_SUBMODULE_END
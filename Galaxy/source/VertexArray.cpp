#include "VertexArray.h"
#include "GL/glew.h"

namespace Galaxy 
{
	VertexArray::VertexArray() : ID(0), count(0), stride(0)
	{
		glGenVertexArrays(1, &ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteBuffers(1, &ID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(ID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
}

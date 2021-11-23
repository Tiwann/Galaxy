#include "VertexArray.h"
#include "GL/glew.h"

namespace Galaxy 
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &ID);
	}

	VertexArray* VertexArray::Create()
	{
		return new VertexArray();
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

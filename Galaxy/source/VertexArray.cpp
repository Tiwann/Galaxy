#include "VertexArray.h"
#include "GL/glew.h"

namespace Galaxy 
{
	VertexArray::VertexArray()
		: ID(0), attribcount(0), stride(0), offset(0)
	{
		glGenVertexArrays(1, &ID);
		attribcount = 0;
		stride = 0;
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

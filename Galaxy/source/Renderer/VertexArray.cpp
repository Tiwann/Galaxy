#include "VertexArray.h"
#include "GL/glew.h"

namespace Galaxy 
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &ID);
		attribcount = 0;
		stride = 0;
	}

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		return std::make_shared<VertexArray>(VertexArray());
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

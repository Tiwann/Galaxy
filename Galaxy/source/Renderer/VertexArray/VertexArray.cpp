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

	template<class T>
	void VertexArray::AddAttribPointer<glm::fvec3>()
	{
		stride += sizeof(glm::fvec3);
		glEnableVertexAttribArray(attribcount);
		glVertexAttribPointer(attribcount, 3, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
		offset += stride;
	}

	template<class T>
	void VertexArray::AddAttribPointer<glm::fvec2>()
	{
		stride += sizeof(glm::fvec2);
		glEnableVertexAttribArray(attribcount);
		glVertexAttribPointer(attribcount, 2, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
		offset += stride;
		attribcount++;
	}
}

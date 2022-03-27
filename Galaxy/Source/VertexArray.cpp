#include "VertexArray.h"
#include "glad/glad.h"

namespace Galaxy 
{
	VertexArray::VertexArray() : ID(0)
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


	void VertexArray::AddLayout(int type, int count)
	{
		layouts.push_back(BufferLayout(type, count));
	}

	template<>
	void VertexArray::AddLayout<float>(int count)
	{
		layouts.push_back(BufferLayout(GL_FLOAT, count));

	}


	void VertexArray::RegisterLayouts()
	{
		unsigned int stride = 0;
		unsigned int offset = 0;

		for (const auto& l : layouts) 
		{
			stride += l.count * BufferLayout::SizeOfType(l.type);
		}

		for (unsigned int i = 0; i < layouts.size(); i++)
		{
			const auto& layout = layouts[i];
			
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, layout.count, layout.type, GL_FALSE, stride, (const void*)offset);
			offset += layout.count * BufferLayout::SizeOfType(layout.type);
		}
		
	}
}

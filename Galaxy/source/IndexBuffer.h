#pragma once
#include "GL/glew.h"

namespace Galaxy
{
	class IndexBuffer
	{
	private:
		unsigned int ID;
	public:
		IndexBuffer();
		~IndexBuffer();
		void SetData(GLsizeiptr size, const void* data);
		void Bind() const;
		void Unbind() const;
	};
}


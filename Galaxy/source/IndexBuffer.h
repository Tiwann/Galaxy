#pragma once
#include "GL/glew.h"
#include <memory>

namespace Galaxy
{
	class IndexBuffer
	{
	private:
		uint32_t ID;
	public:
		IndexBuffer();

		void SetData(GLsizeiptr size, const void* data);
		void Bind() const;
		void Unbind() const;
	};
}


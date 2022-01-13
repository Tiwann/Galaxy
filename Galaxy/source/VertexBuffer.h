#pragma once
#include "Vertex.h"
#include "GL/glew.h"
#include <memory>

namespace Galaxy 
{
	class VertexBuffer
	{
	private:
		uint32_t ID;
	public:
		VertexBuffer();
		void SetData(GLsizeiptr size, const void* data);
		void SetData(Vertices vertices);
		void Bind() const;
		void Unbind() const;
	};
}


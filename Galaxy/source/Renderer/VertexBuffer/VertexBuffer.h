#pragma once
#include "Renderer/Vertex.h"

namespace Galaxy 
{
	class VertexBuffer
	{
	private:
		unsigned int ID;
		VertexBuffer();
	public:
		static VertexBuffer* Create();
		void SetData(GLsizeiptr size, const void* data);
		void SetData(Vertices vertices);
		void Bind() const;
		void Unbind() const;
	};
}


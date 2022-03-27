#pragma once
#include "Vertex.h"
#include "glad/glad.h"
#include <memory>

namespace Galaxy 
{
	class VertexBuffer
	{
	private:
		unsigned int ID;
	public:
		VertexBuffer();
		~VertexBuffer();
		void SetData(GLsizeiptr size, const void* data);
		void SetData(const std::vector<Vertex>& vertices);
		void Bind() const;
		void Unbind() const;
	};
}


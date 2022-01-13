#pragma once
#include "Renderer/Vertex.h"
#include "GL/glew.h"
#include <memory>

namespace Galaxy 
{
	class VertexBuffer
	{
	private:
		uint32_t ID;
		VertexBuffer();
	public:
		static std::shared_ptr<VertexBuffer> Create();
		void SetData(GLsizeiptr size, const void* data);
		void SetData(Vertices vertices);
		void Bind() const;
		void Unbind() const;
	};
}


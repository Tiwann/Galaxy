#pragma once

namespace Galaxy 
{
	class VertexArray
	{
	private:
		unsigned int ID;
		VertexArray();
	public:
		static VertexArray* Create();
	
		void Bind() const;
		void Unbind() const;
		//void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout);
	};
}


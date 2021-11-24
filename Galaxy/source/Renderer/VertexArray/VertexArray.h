#pragma once
#include <glm/glm.hpp>

namespace Galaxy 
{
	class VertexArray
	{
	private:
		unsigned int ID;
		VertexArray();
		uint16_t attribcount;
		uint16_t stride;
		uint16_t offset;
	
	public:
		static VertexArray* Create();
	
		void Bind() const;
		void Unbind() const;

		template<class T>
		void AddAttribPointer();
	};
}


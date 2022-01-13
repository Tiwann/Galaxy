#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace Galaxy 
{
	class VertexArray
	{
	private:
		unsigned int ID;
		uint16_t attribcount;
		uint16_t stride;
		uint16_t offset;
	
	public:
		VertexArray();
	
		void Bind() const;
		void Unbind() const;

		
	};
}


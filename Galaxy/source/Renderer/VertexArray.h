#pragma once
#include <glm/glm.hpp>
#include <memory>

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
		static std::shared_ptr<VertexArray> Create();
	
		void Bind() const;
		void Unbind() const;

		
	};
}


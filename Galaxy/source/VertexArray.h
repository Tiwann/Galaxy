#pragma once
#include <glm/glm.hpp>
#include "VertexBuffer.h"

namespace Galaxy 
{
	class VertexArray
	{
	private:
		unsigned int ID;
		unsigned int count;
		unsigned int stride;
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void Unbind() const;
	};


}


#pragma once
#include "GL/glew.h"
#include <vector>

namespace Galaxy {
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		bool normalized;
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> elements;
	public:
		VertexBufferLayout();

		template<typename T>
		void Push(int count) 
		{
			static_assert(false);
		}

		template<typename T>
		void Push<float>(int count)
		{
			elements.push_back({ GL_FLOAT, count, false });
		}

		template<typename T>
		void Push<unsigned int>(int count)
		{
			elements.push_back({ GL_UNSIGNED_BYTE, count, false });
		}
	};
}


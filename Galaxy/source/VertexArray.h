#pragma once
#include <glm/glm.hpp>
#include "VertexBuffer.h"
#include "BufferLayout.h"


namespace Galaxy 
{
	class VertexArray
	{
	private:
		unsigned int ID;
		std::vector<BufferLayout> layouts;
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void Unbind() const;

		void AddLayout(int count, int type);

		template<typename T>
		void AddLayout(int count);

		template<>
		void AddLayout<float>(int count)
		{
			layouts.push_back(BufferLayout(GL_FLOAT, count));
		}

		void RegisterLayouts();
	};


}


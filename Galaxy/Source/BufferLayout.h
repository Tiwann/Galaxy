#pragma once
#include <glad/glad.h>


namespace Galaxy
{
	struct BufferLayout
	{
		unsigned int type;
		unsigned int count;
		static int SizeOfType(int type);

		BufferLayout(int intype, int incount) : type(intype), count(incount){}
	};
}


#pragma once
#include <GL/glew.h>


namespace Galaxy
{
	struct BufferLayout
	{
		unsigned int type;
		unsigned int count;
		static int SizeOfType(int type);
	};
}


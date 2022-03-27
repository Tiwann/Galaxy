#include "BufferLayout.h"


int Galaxy::BufferLayout::SizeOfType(int type)
{
	switch (type)
	{
		case GL_FLOAT:			return sizeof(GLfloat);
		case GL_UNSIGNED_INT:	return sizeof(GLuint);
		case GL_UNSIGNED_BYTE:	return sizeof(GLubyte);
		case GL_INT:			return sizeof(GLbyte);
		case GL_BYTE:			return sizeof(GLbyte);
		default:				return 0;
	}
	return 0;
}

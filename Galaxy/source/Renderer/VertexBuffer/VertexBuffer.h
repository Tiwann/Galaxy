#pragma once

class VertexBuffer
{
private:
	unsigned int ID;
public:
	VertexBuffer(GLsizeiptr size, const void* data);
	void Bind() const;
	void Unbind() const;
};


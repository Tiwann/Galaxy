#pragma once

namespace Galaxy
{
	class IndexBuffer
	{
	private:
		unsigned int ID;
		IndexBuffer();
	public:
		static IndexBuffer* Create();
		void SetData(GLsizeiptr size, const void* data);
		void Bind() const;
		void Unbind() const;
	};
}


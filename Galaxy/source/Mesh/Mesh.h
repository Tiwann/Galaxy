#include <vector>

#include "Renderer/Vertex.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Shader/Shader.h"


namespace Galaxy
{
	class Mesh
	{
	private:
		Mesh();
		std::vector<VertexArray*> vaos;
	public:
		static Mesh* Create();
		void Draw(Shader* shader, VertexArray* vao);
	};
}

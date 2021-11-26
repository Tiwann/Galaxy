#include "Mesh.h"
#include <GL/glew.h>
namespace Galaxy
{
	Mesh::Mesh()
	{
		
	}
	void Mesh::Draw(Shader* shader, VertexArray* vao)
	{
		shader->UseProgram();
		vao->Bind();
		//glDrawArrays(GL_TRIANGLES, 0, )
	}
}
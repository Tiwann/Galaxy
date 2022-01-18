#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Galaxy
{
	void Transform::Translate(glm::vec3 translation)
	{
		position += translation;
	}

	void Transform::Rotate(glm::vec3 rotation)
	{
		this->rotation += rotation;
	}

	void Transform::Scale(glm::vec3 scale)
	{
		this->scale += scale;
	}


	const glm::mat4& Transform::GetTransformMatrix(bool isView)
	{
		matrix = glm::mat4(1.0f);

		if (isView) matrix = glm::translate(matrix, -position);
		else		matrix = glm::translate(matrix, position);

		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::scale(matrix, scale);
		return matrix;
	}
}




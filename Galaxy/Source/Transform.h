#pragma once

#include <glm/glm.hpp>


namespace Galaxy
{
	class Transform
	{
	private:
		glm::mat4 matrix;
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		
		Transform() : position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)), matrix(glm::mat4(1.0f)) {}
		Transform(glm::vec3 pos) : position(pos), rotation(glm::vec3(0.0f)), scale(glm::vec3(1.0f)), matrix(glm::mat4(1.0f)) {}
		Transform(glm::vec3 pos, glm::vec3 rot) : position(pos), rotation(rot), scale(glm::vec3(1.0f)), matrix(glm::mat4(1.0f)) {}
		Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale) : position(pos), rotation(rot), scale(scale), matrix(glm::mat4(1.0f)) {}
		
		void Translate(glm::vec3 translation);
		void Rotate(glm::vec3 rotation);
		void Scale(glm::vec3 scale);
		
		glm::mat4& Matrix();
	};
}



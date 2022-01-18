#pragma once
#include "Transform.h"

namespace Galaxy
{
	class SceneObject
	{
	private:		
		Transform transform;

	public:
		SceneObject() : transform(Transform()) {}
		Transform& GetTransform() { return transform; }
		glm::vec3& GetPosition()  { return transform.GetPosition(); }
		glm::vec3& GetRotation()  { return transform.GetRotation(); }
		glm::vec3& GetScale()     { return transform.GetScale(); }
	};
}



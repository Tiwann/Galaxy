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
	};
}



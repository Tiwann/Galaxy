#pragma once

#include <vector>

namespace Galaxy
{
	class SceneObject;

	class Scene
	{
	private:
		std::vector<SceneObject*> sceneObjects;
		Scene();
	public:
		static Scene Get();
		void Init();
		void Update();
		void RegisterSceneObject(const SceneObject* object);


		const std::vector<SceneObject*>& GetSceneObjects() const { return sceneObjects; }
	};
}

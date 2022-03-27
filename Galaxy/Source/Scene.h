#pragma once
#include <vector>
#include "imgui.h"
namespace Galaxy
{
	class SceneObject;
	class Scene
	{
	private:
		std::vector<SceneObject*> sceneObjects;
		Scene();
	public:
		static Scene& Get();
		void Init();
		void Update(float delta);
		void OnGuiRender(const ImGuiIO& io) const;
		void AddSceneObject(SceneObject* object);

		const std::vector<SceneObject*>& GetSceneObjects() const { return sceneObjects; }
	};
}

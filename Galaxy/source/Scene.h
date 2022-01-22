#pragma once

#include <vector>
#include "imgui.h"
#include "SceneObject.h"

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
		void Update();
		void OnGuiRender(const ImGuiIO& io);
		void AddSceneObject(SceneObject* object);


		const std::vector<SceneObject*>& GetSceneObjects() const { return sceneObjects; }
	};
}

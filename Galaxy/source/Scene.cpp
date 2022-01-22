#include "Scene.h"
#include "Log.h"

namespace Galaxy
{

	Scene::Scene()
	{
		LOG_TRACE("[SCENE] Creating scene");
	}

	Scene& Scene::Get()
	{
		static Scene instance = Scene();
		return instance;
	}

	void Scene::Init()
	{
	}

	void Scene::Update()
	{
	}

	void Scene::OnGuiRender(const ImGuiIO& io)
	{
		ImGui::Begin("Scene");
	
		const ImGuiSelectableFlags flags = ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick;
		if (ImGui::BeginListBox("Scene Hierarchy"))
		{
			const std::vector<SceneObject*> objects = Get().GetSceneObjects();
			for (SceneObject* object : objects)
			{
				const bool selected = object->GetSelected();
				if (ImGui::Selectable(object->GetName().c_str(), selected, flags))
				{
					object->SetSelected(selected);
				}
				
			}
			ImGui::EndListBox();
		}
		
		ImGui::End();
	}

	void Scene::AddSceneObject(SceneObject* object)
	{
		sceneObjects.push_back(object);
	}
}
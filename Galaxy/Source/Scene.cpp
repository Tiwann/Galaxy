#include "Scene.h"
#include "Window.h"
#include "Log.h"
#include "InputManager.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include <glm/gtc/type_ptr.hpp>



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

	void Scene::Update(float delta)
	{
		
	}

	void Scene::OnGuiRender(const ImGuiIO& io) const
	{
		using namespace ImGui;
		Begin("Scene", nullptr, ImGuiWindowFlags_MenuBar);
		
		if (BeginMenuBar())
		{
			if (BeginMenu("Add"))
			{
				if (MenuItem("Mesh"))
				{

					
				}
				

				if (BeginMenu("Lighting"))
				{
					if (MenuItem("Directional Light"))
					{
						auto* newLight = new DirectionalLight();
					}
					EndMenu();
				}
				

				if (MenuItem("Camera"))
				{
					using Galaxy::CameraMode;
					new Camera(CameraMode::PERSP, 1280, 720, 0.01f, 100.0f);
				}
				EndMenu();
			}
			if (BeginMenu("File"))
			{
				if(BeginMenu("Import"))
				{
					if (MenuItem("Wavefront OBJ (.obj)"))
					{
						
					}
					EndMenu();
				}
				EndMenu();
			}
			EndMenuBar();
		}
		const ImGuiSelectableFlags flags = ImGuiSelectableFlags_SpanAllColumns;
		if (BeginListBox("##Scene Hierarchy", ImVec2(-FLT_MIN, -FLT_MIN)))
		{	
			const std::vector<SceneObject*> objects = Get().GetSceneObjects();
			static int selection = -1;
			for (unsigned int i = 0; i < objects.size(); i++)
			{
				if (Selectable(objects[i]->GetName().c_str(), selection == i, flags))
				{
					selection = i;
					for (unsigned int j = 0; j < objects.size(); j++)
					{
						if(!InputManager::GetKeyPressed(KeyCode::LEFT_CONTROL))
							objects[j]->SetSelected(false);
						objects[selection]->SetSelected(true);
#if 0
						if(Camera* camera = dynamic_cast<Camera*>(objects[j]))
						{
							bool ortho = camera->GetMode() == CameraMode::ORTHO ? true : false;
							ImGuizmo::SetOrthographic(ortho);
							ImGuizmo::SetDrawlist();
							ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
							ImGuizmo::Manipulate(glm::value_ptr(camera->GetViewMatrix()), glm::value_ptr(camera->GetProjectionMatrix()),
								ImGuizmo::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(objects[selection]->GetTransform().Matrix()));
						}
#endif
					}	
				}
			}
			EndListBox();
		}
		
		End();
	}

	void Scene::AddSceneObject(SceneObject* object)
	{
		sceneObjects.push_back(object);
	}
}

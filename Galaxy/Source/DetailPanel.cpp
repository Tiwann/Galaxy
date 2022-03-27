#include "DetailPanel.h"
#include "SceneObject.h"
#include "Scene.h"
#include "Camera.h"

#include <glm/gtc/type_ptr.hpp>


namespace Galaxy
{
	void DetailPanel::OnGuiRender(const ImGuiIO& io)
	{
        ImGui::Begin("Galaxy Panel");
        for (SceneObject* object : Scene::Get().GetSceneObjects()) 
        {
            object->OnGuiRender(io);
        }
        ImGui::End();
	}
}


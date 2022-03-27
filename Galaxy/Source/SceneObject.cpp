#include "SceneObject.h"

#include <glm/gtc/type_ptr.hpp>

namespace Galaxy
{
	bool SceneObject::AttachTo(SceneObject* parent)
	{
		if (parent->canHaveChilds)
		{
			parent->childs.push_back(this);
			return true;
		} else return false;
	}


	bool SceneObject::DetachFrom(SceneObject* parent)
{
		std::vector<SceneObject*>::iterator iterator = std::find(parent->childs.begin(), parent->childs.end(), this);
		if (iterator != parent->childs.end())
		{
			auto index = std::distance(parent->childs.begin(), iterator);
			parent->childs.erase(parent->childs.begin() + index);
			return true;
		}
		return false;
	}

	bool SceneObject::Rename(const std::string& newName)
	{
		if (name != "")
		{
			name = name != newName ? newName : name;
			return true;
		}
		return false;
	}

	void SceneObject::Register(SceneObject* obj)
	{
		Scene::Get().AddSceneObject(obj);
	}

	void SceneObject::OnGuiRender(const ImGuiIO& io)
	{
		if (GetSelected() && ImGui::TreeNodeEx(GetName().c_str(), treeNodeFlags))
		{
			if (ImGui::TreeNodeEx("Transform", treeNodeFlags))
			{
				ImGui::DragFloat3("Position", glm::value_ptr(transform.position), 0.01f);
				ImGui::DragFloat3("Rotation", glm::value_ptr(transform.rotation), 0.01f);
				ImGui::DragFloat3("Scale", glm::value_ptr(transform.scale), 0.01f);
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
	}
}


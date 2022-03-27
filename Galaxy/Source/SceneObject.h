#pragma once
#include "Transform.h"
#include "Scene.h"
#include <vector>
#include <string>
#include <imgui.h>


namespace Galaxy
{
	class SceneObject
	{
	protected:		
		Transform transform;
		SceneObject* parent;
		std::vector<SceneObject*> childs;
		bool canHaveChilds;
		std::string name;
		bool isSelected;

		const ImGuiTreeNodeFlags treeNodeFlags =	ImGuiTreeNodeFlags_DefaultOpen |
													ImGuiTreeNodeFlags_Framed |
													ImGuiTreeNodeFlags_SpanAvailWidth |
													ImGuiTreeNodeFlags_AllowItemOverlap |
													ImGuiTreeNodeFlags_FramePadding;
	public:
		SceneObject(bool canHaveChilds = true, const std::string& name = "NewSceneObject") : transform(Transform()),
				parent(nullptr), childs(std::vector<SceneObject*>(0, nullptr)), canHaveChilds(canHaveChilds), name(name), isSelected(false) 
		{
			Register(this);
		}
		

		Transform& GetTransform() { return transform; }
		const std::string& GetName() { return name; }
		bool& GetSelected() { return isSelected; }
		void SetSelected(bool newSelected) { isSelected = newSelected; }
		bool AttachTo(SceneObject* parent);
		bool DetachFrom(SceneObject* parent);
		bool Rename(const std::string& newName);
		void Register(SceneObject* obj);
		virtual void OnGuiRender(const ImGuiIO& io);
		
	};
}



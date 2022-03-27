#include "DirectionalLight.h"

#include "glm/gtc/type_ptr.hpp"

namespace Galaxy
{
	void DirectionalLight::SetDirection(const glm::vec3& newDirection)
	{
		direction = newDirection;
	}

	void DirectionalLight::OnGuiRender(const ImGuiIO& io)
	{
		SceneObject::OnGuiRender(io);
		ImGuiColorEditFlags colorflags = ImGuiColorEditFlags_Float | ImGuiColorEditFlags_DefaultOptions_;
		
		if(GetSelected() && ImGui::TreeNodeEx("Parameters", treeNodeFlags))
		{
			ImGui::ColorEdit4("Light Color", glm::value_ptr(color), colorflags);
			ImGui::DragFloat("Intensity", &intensity, 0.1f, 0, 0, "%.1f");
			ImGui::BeginDisabled();
			ImGui::DragFloat3("Light Direction", glm::value_ptr(transform.position), 1, 0, 0, "%.1f", ImGuiSliderFlags_NoInput);
			ImGui::EndDisabled();
			ImGui::TreePop();	
		}
	}
}

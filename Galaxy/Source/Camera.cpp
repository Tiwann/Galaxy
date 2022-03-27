#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include "Transform.h"

namespace Galaxy
{
	
	void Camera::SetMode(const CameraMode& newMode)
	{
		if (mode != newMode) mode = newMode;
	}

	const glm::mat4& Camera::GetProjectionMatrix()
	{
		switch (mode)
		{
		case CameraMode::ORTHO:
			projection = glm::ortho(-width / (8 * scale), width / (8 * scale), -height / (8 * scale), height / (8 * scale),
				znear, zfar);
			return projection;

		case CameraMode::PERSP:
			projection = glm::perspective(glm::radians(fov), width / height, znear, zfar);
			return projection;
		}
		assert(false);
		const glm::mat4 identity = glm::mat4(1.0f);
		return identity;
	}
	
	const glm::mat4& Camera::GetViewMatrix()
	{
		view = inverse(transform.Matrix());
		return view;
	}

	void Camera::OnGuiRender(const ImGuiIO& io)
	{
		SceneObject::OnGuiRender(io);

		if (GetSelected())
		{
			if (ImGui::TreeNodeEx("Parameters", treeNodeFlags))
			{
				const char* items[]{ "Orthographic", "Perspective" };
				static int selectedItem = (int)GetMode();
				ImGui::Combo("Camera Mode", &selectedItem, items, IM_ARRAYSIZE(items));
				switch (selectedItem) {
				case 0:
					SetMode(Galaxy::CameraMode::ORTHO);
					ImGui::DragFloat("Orthographic Scale", &scale, 0.1f);
					break;
				case 1:
					SetMode(Galaxy::CameraMode::PERSP);
					ImGui::DragFloat("Field Of View", &fov, 0.1f, 0.0f, 0.0f, "%.1f Degrees");
					break;
				}
				ImGui::TreePop();
			}
		}
	}
}


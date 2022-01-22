#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneObject.h"



namespace Galaxy 
{
	enum class CameraMode : int
	{
		ORTHO = 0,
		PERSP = 1,
	};

	class Camera : public SceneObject
	{
	protected:
		float width, height;
		float znear, zfar;
		float fov, scale;
		glm::mat4 projection;
		CameraMode mode;
	public:
		Camera(CameraMode mode, float width, float height, 
			float znear, float zfar, 
			float fov = 45.0f, float scale = 45.0f) 
			: mode(mode), width(width), height(height), 
			znear(znear), zfar(zfar), 
			fov(fov), scale(scale), projection(glm::mat4(1.0f)), SceneObject(false, "Camera") {}

		float& GetFieldOfView() { return fov; }
		float& GetOrthoScale() { return scale;  }

		virtual void OnGuiRender(const ImGuiIO& io) override;
		void SetMode(const CameraMode& newMode);
		const CameraMode& GetMode() const { return mode;  }

		const glm::mat4& GetProjectionMatrix();
		const glm::mat4& GetViewMatrix();
	};
}



#pragma once

#include "Transform.h"

namespace Galaxy 
{

	enum class CameraMode
	{
		ORTHO = 0,
		PERSP = 1
	};

	class Camera
	{
	private:
		CameraMode mode;
		float zfar, znear, width, height;
		glm::mat4 view;
		glm::mat4 projection;

	public:
		Transform transform;
		float  scale, fov;
		Camera();

		void SetPerspective(float fov, float znear, float zfar, float width, float height);
		void SetOrtho(float scale, float znear, float zfar, float width, float height);
		void Update(const CameraMode& newMode);

		// Getters
		const CameraMode GetMode() const { return mode; }
		const glm::mat4& GetViewProjMatrix() const { return view * projection; }
		const glm::mat4& GetViewMatrix() const { return view ; }
		const glm::mat4& GetProjectionMatrix() const { return projection; }
	};
}



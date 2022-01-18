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
			projection = glm::ortho(-width / (2 * scale), width / (2 * scale), -height / (2 * scale), height / (2 * scale),
				znear, zfar);
			return projection;

		case CameraMode::PERSP:
			projection = glm::perspective(glm::radians(fov), width / height, znear, zfar);
			return projection;
		}
		assert(false);
		return glm::mat4(1.0f);
	}
}


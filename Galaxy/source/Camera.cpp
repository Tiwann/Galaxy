#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>



namespace Galaxy
{
	Camera::Camera() 
		: mode(CameraMode::ORTHO), znear(0.0f), zfar(0.0f), width(0.0f), height(0.0f), scale(0.0f), fov(0.0f),
		view(glm::mat4(1.0)), projection(glm::mat4(1.0f)),
		transform({glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f)})
	{

	}


	void Camera::SetPerspective(float fov, float znear, float zfar, float width, float height)
	{
		this->fov = fov;
		this->znear = znear;
		this->zfar = zfar;
		this->width = width;
		this->height = height;
		mode = CameraMode::PERSP;
		view = glm::translate(glm::mat4(1.0f), transform.position);
		//view = glm::rotate(view, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::rotate(view, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		//view = glm::rotate(view, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		projection = glm::perspective(glm::radians(fov), width / height, znear, zfar);
	}

	void Camera::SetOrtho(float scale, float znear, float zfar, float width, float height)
	{
		this->scale = scale;
		this->znear = znear;
		this->zfar = zfar;
		this->height = height;
		this->width = width;
		mode = CameraMode::ORTHO;
		view = glm::translate(glm::mat4(1.0f), transform.position);
		//view = glm::rotate(view, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		//view = glm::rotate(view, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		//view = glm::rotate(view, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		projection = glm::ortho(-width / (2 * scale), width / (2 * scale), -height / (2 * scale), height / (2 * scale), znear, zfar);


	}

	void Camera::Update(const CameraMode& newMode)
	{
		mode = newMode;
		switch(mode)
		{
			case CameraMode::ORTHO: SetOrtho(scale, znear, zfar, width, height); break;
			case CameraMode::PERSP: SetPerspective(fov, znear, zfar, width, height); break;
		}

	}
}


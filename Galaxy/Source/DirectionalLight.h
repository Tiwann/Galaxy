#pragma once
#include "SceneObject.h"

#include <string>
#include <glm/glm.hpp>
namespace Galaxy
{
	class DirectionalLight : public SceneObject
	{
	protected:
		float intensity;
		glm::vec3 direction;
		glm::vec4 color;

	public:
		DirectionalLight(const std::string& name = "Directional Light") 
			: SceneObject(false, name), intensity(0), direction(glm::vec3(1.0f)), color(glm::vec4(1.0f)) {}
		const float& GetIntensity() { return intensity; }
		const glm::vec3& GetDirection() { return direction; }
		void SetDirection(const glm::vec3& newDirection);
		glm::vec4& GetColor() { return color; }
		
		virtual void OnGuiRender(const ImGuiIO& io) override;
	};
}


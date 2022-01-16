#pragma once

#include <glm/glm.hpp>

namespace Galaxy
{
	class Vector3 : public glm::vec3
	{
	public:
		Vector3() : glm::vec3(0){}
		Vector3(float x, float y, float z) : glm::vec3(x, y, z){}
		Vector3(int x, int y, int z) : glm::vec3(x, y, z) {}
		Vector3(double x, double y, double z) : glm::vec3(x, y, z) {}
		Vector3(float d) : glm::vec3(d){}
		static Vector3 Up;
		static Vector3 Right;
		static Vector3 Forward;
		static Vector3 Left;
		static Vector3 Down;
		static Vector3 Backward;
	};

	Vector3 Vector3::Up			= Vector3(0.0f, 1.0f, 0.0f);
	Vector3 Vector3::Right		= Vector3(1.0f, 0.0f, 0.0f);
	Vector3 Vector3::Forward	= Vector3(0.0f, 0.0f, 1.0f);
	Vector3 Vector3::Left		= Vector3(-1.0f, 0.0f, 0.0f);
	Vector3 Vector3::Down		= Vector3(0.0f, -1.0f, 0.0f);
	Vector3 Vector3::Backward	= Vector3(0.0f, 0.0f, -1.0f);

}

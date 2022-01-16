#pragma once

#include <glm/glm.hpp>

namespace Galaxy
{
	class Vector2 : public glm::vec2
	{
	public:
		Vector2(float x, float y) : glm::vec2(x, y) {}

		static Vector2 Up;
		static Vector2 Down;
		static Vector2 Left;
		static Vector2 Right;

	};

	Vector2 Vector2::Up = Vector2(0.0f, 1.0f);
	Vector2 Vector2::Down = Vector2(0.0f, -1.0f);
	Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);
	Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
}


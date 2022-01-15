/// @ref core
/// @file glm/vec3.hpp

#pragma once
#include "./ext/vector_bool3.hpp"
#include "./ext/vector_bool3_precision.hpp"
#include "./ext/vector_float3.hpp"
#include "./ext/vector_float3_precision.hpp"
#include "./ext/vector_double3.hpp"
#include "./ext/vector_double3_precision.hpp"
#include "./ext/vector_int3.hpp"
#include "./ext/vector_int3_sized.hpp"
#include "./ext/vector_uint3.hpp"
#include "./ext/vector_uint3_sized.hpp"

namespace glm {
	namespace vector3
	{
		static vec3 up(0.0f, 1.0f, 0.0f);
		static vec3 right(1.0f, 0.0f, 0.0f);
		static vec3 forward(0.0f, 0.0f, 1.0f);

		static vec3 down = -up;
		static vec3 left = -right;
		static vec3 backward = -forward;
	}

	namespace vector2
	{
		static vec2 up(0.0f, 1.0f);
		static vec2 right(1.0f, 0.0f);
		static vec2 down = -up;
		static vec2 left = -right;
	}
}

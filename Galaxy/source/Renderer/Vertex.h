#pragma once
#include <glm/glm.hpp>

namespace Galaxy {
	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};
}

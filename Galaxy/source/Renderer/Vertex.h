#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace Galaxy {
	struct Vertex {
		glm::fvec3 position;
		glm::fvec2 texCoord;
		glm::fvec3 normal;
		glm::fvec4 color;

		static size_t GetSize() { return 2 * sizeof(glm::fvec3) + sizeof(glm::fvec4) + sizeof(glm::fvec2); }
	};

	typedef std::vector<Vertex> Vertices;
}

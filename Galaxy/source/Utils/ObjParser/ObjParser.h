#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>


namespace Galaxy 
{	
	struct ObjData
	{
		std::vector<glm::fvec3> positions;
		std::vector<glm::fvec2> texCoords;
		std::vector<glm::fvec3> normals;

	};

	class ObjParser
	{
	public:
		static ObjData ParseFile(const std::string filepath);
	};
}


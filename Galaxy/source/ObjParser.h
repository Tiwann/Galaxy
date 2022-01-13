#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

#include "Vertex.h"


namespace Galaxy 
{	
	struct ObjData
	{
		std::vector<std::string> objects;
		std::vector<glm::fvec3> positions;
		std::vector<glm::fvec2> texCoords;
		std::vector<glm::fvec3> normals;
		std::vector<glm::ivec3> indices;
	};

	class ObjParser
	{
	public:
		static ObjData ParseFile(const std::string filepath);
		static Vertices DataToVertices(const ObjData objdata);
		static Vertices DataToVertices(const ObjData objdata, std::vector<unsigned int>& out_glindices);
		static Vertices ParseFileToVertices(const std::string filepath) { return DataToVertices(ParseFile(filepath)); }

		// We don't want to initialize this class!
		ObjParser() = delete;
		ObjParser(const ObjParser& other) = delete;
		void operator=(const ObjParser& other) = delete;
	};
}


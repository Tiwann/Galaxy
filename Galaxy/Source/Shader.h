#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Texture2D.h"

namespace Galaxy {
	class Shader
	{
	private:
		std::string vertSource;
		std::string fragSource;

		std::string vertPath;
		std::string fragPath;

		unsigned int vertID;
		unsigned int fragID;
		unsigned int programID;

		bool isCompiled;
		bool isLinked;
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		~Shader();
		unsigned int GetProgram() const { return programID; }
		void PrintSource();
		void Compile();
		void Link();
		void UseProgram() const;
		void Delete();

		void SetUniformData1f(const std::string& name, const float& data) const;
		void SetUniformData2f(const std::string& name, const glm::vec2& data) const;
		void SetUniformData3f(const std::string& name, const glm::vec3& data) const;
		void SetUniformData4f(const std::string& name, const glm::vec4& data) const;
					   
		void SetUniformData1i(const std::string& name, const int& data) const;
		void SetUniformData2i(const std::string& name, const glm::ivec2& data) const;
		void SetUniformData3i(const std::string& name, const glm::ivec3& data) const;
		void SetUniformData4i(const std::string& name, const glm::ivec4& data) const;
		void SetUniformDataMat4f(const std::string& name, const glm::mat4& data) const;


	private:
		std::string Read(const std::string& file);
	};

}


#include "Shader.h"
#include <fstream>
#include <format>
#include "GL/glew.h"
#include <iostream>
#include <sstream>

namespace Galaxy {
	Shader::Shader(const std::string vertPath, const std::string fragPath)
	{
		Shader::vertSource = Shader::Read(vertPath);
		Shader::fragSource = Shader::Read(fragPath);

		vertID = glCreateShader(GL_VERTEX_SHADER);
		fragID = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertID, 1, &vertSource, nullptr);
		glShaderSource(fragID, 1, &fragSource, nullptr);

		programID = glCreateProgram();
		glAttachShader(programID, vertID);
		glAttachShader(programID, fragID);
	}

	const char* Shader::Read(const std::string file) const
	{
		std::ifstream stream(file, std::ios::in);

		if (!stream.is_open()) {
			std::cerr << std::format("{} is not a correct file path!", file) << std::endl;
		}

		std::stringstream ss;
		ss << stream.rdbuf();
		std::string content = ss.str();
		stream.close();
		return content.c_str();
	}
}

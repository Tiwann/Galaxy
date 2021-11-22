#include "Shader.h"
#include <fstream>
#include <format>
#include <iostream>
#include <sstream>

namespace Galaxy {
	Shader::Shader(const std::string vertPath, const std::string fragPath)
	{
		vertSource = Read(vertPath).c_str();
		fragSource = Read(fragPath).c_str();
	}

	std::string Shader::Read(const std::string file)
	{
		std::ifstream stream(file, std::ios::in);

		if (!stream.is_open()) {
			std::cerr << std::format("{} is not a correct file path!", file) << std::endl;
		}

		std::stringstream ss;
		ss << stream.rdbuf();
		std::string content = ss.str();
		stream.close();
		return content;
	}
}

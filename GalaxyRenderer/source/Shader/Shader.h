#pragma once
#include <string>

namespace Galaxy {
	class Shader
	{
	public:
		const char* vertSource;
		const char* fragSource;

		Shader(const std::string vertPath, const std::string fragPath);

		void Compile() const;
		void Link() const;
		void UseProgram() const;
	private:
		std::string Read(const std::string file);
	};
}


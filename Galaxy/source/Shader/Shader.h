#pragma once
#include <string>

namespace Galaxy {
	class Shader
	{
	private:
		const char* vertSource;
		const char* fragSource;

		unsigned int vertID;
		unsigned int fragID;
		unsigned int programID;
	public:
		Shader(const std::string vertPath, const std::string fragPath);

		void Compile() const;
		void Link() const;
		void UseProgram() const;
	private:
		const char* Read(const std::string file) const;
	};
}


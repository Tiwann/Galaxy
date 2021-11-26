#pragma once
#include <string>

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
		Shader(const std::string vertPath, const std::string fragPath);
	public:
		static Shader* Create(const std::string vertPath, const std::string fragPath);
		uint32_t GetProgram() const { return programID; }
		void PrintSource();
		void Compile();
		void Link();
		void UseProgram() const;
		void Delete();
	private:
		std::string Read(const std::string file);
	};
}


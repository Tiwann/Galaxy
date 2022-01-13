#pragma once
#include <string>
#include <memory>

namespace Galaxy {
	class Shader
	{
	private:
		std::string vertSource;
		std::string fragSource;

		std::string vertPath;
		std::string fragPath;

		uint32_t vertID;
		uint32_t fragID;
		uint32_t programID;

		bool isCompiled;
		bool isLinked;
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);
		uint32_t GetProgram() const { return programID; }
		void PrintSource();
		void Compile();
		void Link();
		void UseProgram() const;
		void Delete();
	private:
		std::string Read(const std::string& file);
	};
}


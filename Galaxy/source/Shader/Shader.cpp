#include "Shader.h"
#include <fstream>
#include <format>
#include "GL/glew.h"
#include <iostream>
#include <sstream>
#include "Log/Log.h"

namespace Galaxy {
	Shader::Shader(const std::string& vertFile, const std::string& fragFile)
	{
		vertPath = std::format("Assets/Shaders/{}", vertFile);
		fragPath = std::format("Assets/Shaders/{}", fragFile);

		vertSource = Shader::Read(vertPath);
		fragSource = Shader::Read(fragPath);

		vertID = glCreateShader(GL_VERTEX_SHADER);
		fragID = glCreateShader(GL_FRAGMENT_SHADER);

		const char* vs = vertSource.c_str();
		const char* fs = fragSource.c_str();

		glShaderSource(vertID, 1, &vs, nullptr);
		glShaderSource(fragID, 1, &fs, nullptr);

		programID = glCreateProgram();
		glAttachShader(programID, vertID);
		glAttachShader(programID, fragID);

		delete vs;
		delete fs;
	}

	void Shader::Compile()
	{
		if (vertSource == "" || fragSource == "")
		{
			Shader::isCompiled = false;
			return;
		}

		int compiled;

		// Compile Vertex
		glCompileShader(vertID);
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &compiled);

		if (compiled == GL_TRUE)
		{
			LOG_INFO("[SHADER] Successfully compiled vertex shader from {}!", vertPath);
		}
		else
		{
			LOG_ERROR("[SHADER] Failed to compile vertex shader from {}!", vertPath);
			Shader::isCompiled = false;
			int length = 0;
			char message[1024];
			glGetShaderInfoLog(vertID, 1024, &length, message);
			LOG_ERROR(message);
		}

		// Compile Fragment
		glCompileShader(fragID);
		glGetShaderiv(fragID, GL_COMPILE_STATUS, &compiled);

		if (compiled == GL_TRUE)
		{
			LOG_INFO("[SHADER] Successfully compiled fragment shader from {}!", fragPath);
		}
		else
		{
			LOG_ERROR("[SHADER] Failed to compile fragment shader from {}!", fragPath);
			Shader::isCompiled = false;
			int length = 0;
			char message[1024];
			glGetShaderInfoLog(fragID, 1024, &length, message);
			LOG_ERROR(message);
		}

		Shader::isCompiled = true;
	}

	void Shader::Link()
	{
		if (!Shader::isCompiled) {
			LOG_ERROR("[SHADER] Cannot link shaders, compilation failed.");
			return;
		}

		glLinkProgram(programID);
		int linked;
		glGetProgramiv(programID, GL_LINK_STATUS, &linked);

		if (linked == GL_TRUE)
		{
			LOG_INFO("[SHADER] Shader program successfully linked!\n");
			Shader::isLinked = true;
		}
		else
		{
			LOG_ERROR("[SHADER] Failed to link shader program!");
			Shader::isLinked = false;
			int length = 0;
			char message[1024];
			glGetProgramInfoLog(programID, 1024, &length, message);
			LOG_ERROR(message);
		}
	}

	void Shader::UseProgram() const
	{
		
		if (!Shader::isLinked)
		{
			LOG_ERROR("[SHADER] An error occured, cannot use this shader.");
			assert(Shader::isLinked);
		}
		glUseProgram(programID);
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& vertPath, const std::string& fragPath)
	{
		return std::make_shared<Shader>(Shader(vertPath, fragPath));
	}

	void Shader::PrintSource()
	{
		std::cout << vertSource << std::endl;
		std::cout << fragSource << std::endl;
	}

	std::string Shader::Read(const std::string& file)
	{
		std::ifstream stream(file, std::ios::in);

		if (!stream.is_open()) {
			LOG_ERROR("[SHADER] Fail to read shader file at {}", file);
			stream.close();
			return "";
		}

		LOG_TRACE("[SHADER] Reading file {}", file);
		std::stringstream ss;
		ss << stream.rdbuf();
		stream.close();
		return ss.str();
	}

	void Shader::Delete()
	{
		glDeleteShader(vertID);
		glDeleteShader(fragID);
	}
}

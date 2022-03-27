#include "Shader.h"
#include "glad/glad.h"
#include "Log.h"

#include <fstream>
#include <sstream>

#include "glm/gtc/type_ptr.hpp"

namespace Galaxy {
	Shader::Shader(const std::string& vertFile, const std::string& fragFile)
		: vertSource(""), fragSource(""), vertPath(""), fragPath(""), 
		vertID(0), fragID(0), programID(0), isLinked(false), isCompiled(false)
	{
		vertPath = "Assets/Shaders/" + vertFile;
		fragPath = "Assets/Shaders/" + fragFile;

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
	}

	Shader::~Shader()
	{
		Delete();
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

	void Shader::PrintSource()
	{
		LOG_TRACE(vertSource);
		LOG_TRACE(fragSource);
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

	void Shader::SetUniformData1f(const std::string& name, const float& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform1fv(location, 1, &data);
	}
	
	void Shader::SetUniformData2f(const std::string& name, const glm::vec2& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform2fv(location, 1, glm::value_ptr(data));
	}

	void Shader::SetUniformData3f(const std::string& name, const glm::vec3& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform3fv(location, 1, glm::value_ptr(data));
	}

	void Shader::SetUniformData4f(const std::string& name, const glm::vec4& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform4fv(location, 1, glm::value_ptr(data));
	}

	void Shader::SetUniformData1i(const std::string& name, const int& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform1iv(location, 1, &data);
	}
	void Shader::SetUniformData2i(const std::string& name, const glm::ivec2& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform2iv(location, 1, glm::value_ptr(data));
	}
	void Shader::SetUniformData3i(const std::string& name, const glm::ivec3& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform3iv(location, 1, glm::value_ptr(data));
	}
	void Shader::SetUniformData4i(const std::string& name, const glm::ivec4& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform4iv(location, 1, glm::value_ptr(data));
	}

	void Shader::SetUniformDataMat4f(const std::string& name, const glm::mat4& data) const
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniformMatrix4fv(location, 1, false, glm::value_ptr(data));
	}
	
}

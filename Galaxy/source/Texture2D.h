#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Shader.h"

namespace Galaxy {
	
	struct TextureParams
	{
		unsigned int format;	// GL_RGBA
		unsigned int filter;	// GL_NEAREST | GL_LINEAR
		unsigned int wrap;		// GL_REPEAT

		static TextureParams Default;
		static TextureParams Repeat;
		static TextureParams Mirror;
	};


	class Texture2D
	{
	private:
		unsigned int ID;
		unsigned int slot;
		std::string path;
		TextureParams params;
		int width, height, channels;
		unsigned char* data;

	public:
		Texture2D(const std::string& file, int slot, const TextureParams& params);
		~Texture2D();
		void Bind() const;
		void Unbind() const;
		void Delete() const;
		void SetUniformData(const Shader& shader, const std::string uniform, unsigned int unit) const;

		const int GetWidth() const { return width; }
		const int GetHeight() const { return height; }

	};
}


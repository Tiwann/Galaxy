#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Shader/Shader.h"

namespace Galaxy {
	
	/// <summary>
	/// Define several parameters for texture creation
	/// </summary>
	struct TextureParams
	{
		uint32_t slot;		// GL_TEXTUREX
		uint32_t format;	// GL_RGBA
		uint32_t filter;	// GL_NEAREST | GL_LINEAR
		uint32_t wrap;		// GL_REPEAT
	};


	class Texture2D
	{
	private:
		uint32_t ID;
		uint32_t slot;
		int width, height, channels;
		unsigned char* data;
		Texture2D(const std::string file, const TextureParams params);
	public:
		static Texture2D* Create(const std::string file, const TextureParams params);
		void Bind() const;
		void Unbind() const;
		void Delete() const;
		void SetUniformData(Shader* shader, std::string uniform, uint32_t unit) const;
		const unsigned char* GetData() const { return data; }
	};
}


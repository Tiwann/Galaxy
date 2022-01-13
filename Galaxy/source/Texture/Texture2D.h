#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "Shader/Shader.h"

namespace Galaxy {
	
	struct TextureParams
	{
		uint32_t format;	// GL_RGBA
		uint32_t filter;	// GL_NEAREST | GL_LINEAR
		uint32_t wrap;		// GL_REPEAT

		static TextureParams Default;
		static TextureParams Repeat;
		static TextureParams Mirror;
	};


	class Texture2D
	{
	private:
		uint32_t ID;
		uint32_t slot;
		std::string path;
		TextureParams params;
		int width, height, channels;
		unsigned char* data;
		Texture2D(const std::string file, int32_t slot, const TextureParams& params);

	public:
		static std::shared_ptr<Texture2D> Create(const std::string file, int32_t slot, const TextureParams& params);
		void Bind() const;
		void Unbind() const;
		void Delete() const;
		void SetUniformData(std::shared_ptr<Shader> shader, const std::string uniform, uint32_t unit) const;

		const int32_t GetWidth() const { return width; }
		const int32_t GetHeight() const { return height; }

	};
}


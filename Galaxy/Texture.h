#pragma once
#include <glm/glm.hpp>
#include <string>

namespace Galaxy {
	
	struct TextureParameters 
	{
		glm::ivec2 filter;
		glm::ivec2 wrap;
	};

	class Texture2D
	{
	private:
		uint32_t ID;
		uint32_t slot;
		int width, height, channels;
		unsigned char* data;
		Texture2D(const std::string file, uint32_t slot, uint32_t format, TextureParameters params);
	public:
		Texture2D* Create(const std::string file, uint32_t slot, uint32_t format, TextureParameters params);
		void Bind() const;
		void Unbind() const;
		void Delete() const;

		const unsigned char* GetData() const { return data; }
	};
}


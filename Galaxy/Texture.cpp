#include "Texture.h"
#include <GL/glew.h>
#include <stb/stb_image.h>
#include <Log/Log.h>

namespace Galaxy
{
    Texture2D::Texture2D(const std::string file, uint32_t slot, uint32_t format, TextureParameters params)
    {
        this->slot = slot;
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(file.c_str(), &width, &height, &channels, 0);

        glGenTextures(1, &ID);
        glActiveTexture(this->slot);
        glBindTexture(this->slot, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter.x);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter.y);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap.x);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap.y);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(this->slot, 0);
    }

    Texture2D* Galaxy::Texture2D::Create(const std::string file, uint32_t slot, uint32_t format, TextureParameters params)
    {
        return new Texture2D(file, slot, format, params);
    }

    void Texture2D::Bind() const
    {
        glBindTexture(slot, ID);
    }

    void Texture2D::Unbind() const
    {
        glBindTexture(slot, 0);
    }

    void Texture2D::Delete() const
    {
        stbi_image_free(data);
        glDeleteTextures(1, &ID);
    }
}

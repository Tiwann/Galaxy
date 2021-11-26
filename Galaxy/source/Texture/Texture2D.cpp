#include "Texture2D.h"
#include <GL/glew.h>
#include <stb/stb_image.h>
#include <Log/Log.h>

namespace Galaxy
{
    Texture2D::Texture2D(const std::string file, const TextureParams params)
    {       
        this->slot = slot;
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(file.c_str(), &width, &height, &channels, 0);

        glGenTextures(1, &ID);
        glActiveTexture(this->slot);
        glBindTexture(this->slot, ID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap);

        glTexImage2D(GL_TEXTURE_2D, 0, params.format, width, height, 0, params.format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(this->slot, 0);
        LOG_INFO("[TEXTURE2D] Successfully created Texture2D from {}!", file);
        LOG_TRACE("[TEXTURE2D]-----Width: {} | Height: {}", width, height);
    }

    Texture2D* Galaxy::Texture2D::Create(const std::string file, TextureParams params)
    {
        return new Texture2D(file, params);
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

    void Texture2D::SetUniformData(Shader* shader, std::string uniform, uint32_t unit) const
    {
        uint32_t texuni = glGetUniformLocation(shader->GetProgram(), uniform.c_str());
        shader->UseProgram();
        glUniform1i(texuni, unit);
    }
}

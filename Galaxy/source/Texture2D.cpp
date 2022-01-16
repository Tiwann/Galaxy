#include "Texture2D.h"
#include <GL/glew.h>
#include <stb/stb_image.h>
#include "Log.h"
#include <fstream>


namespace Galaxy
{
    TextureParams TextureParams::Default =  { GL_RGBA, GL_NEAREST, GL_REPEAT };
    TextureParams TextureParams::Repeat =   { GL_RGBA, GL_NEAREST, GL_REPEAT };
    TextureParams TextureParams::Mirror =   { GL_RGBA, GL_NEAREST, GL_MIRRORED_REPEAT };
  

    Texture2D::Texture2D(const std::string& file, int32_t slot, const TextureParams& params)
        : ID(0), slot(slot), width(0), height(0), channels(0), data(nullptr), path(file), params(params)
    {       
        
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(file.c_str(), &width, &height, &channels, 0);
        
        if (!data) 
        {
            LOG_ERROR("[TEXTURE2D] Failed to create Texture2D.");
            return;
        }
        
        glGenTextures(1, &ID);
        
        
        Bind();
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.wrap);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.wrap);

        glTexImage2D(GL_TEXTURE_2D, 0, params.format, width, height, 0, params.format, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        LOG_INFO("[TEXTURE2D] Successfully created Texture2D from {}!", file);
        LOG_TRACE("[TEXTURE2D]-----Width: {} | Height: {}\n", width, height);

        Unbind();
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &ID);
    }

    void Texture2D::Bind() const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, ID);
    }

    void Texture2D::Unbind() const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture2D::Delete() const
    {
        glDeleteTextures(1, &ID);
    }
}

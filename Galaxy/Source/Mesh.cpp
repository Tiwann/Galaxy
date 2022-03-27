#include "Mesh.h"

#include "ObjParser.h"
#include "Log.h"
#include <glad/glad.h>

namespace Galaxy
{

    Mesh::Mesh(const std::vector<Vertex>& vertices, const Shader& shader, const std::string& in_name)
        : SceneObject(true, in_name), vao(VertexArray()),  vbo(VertexBuffer()), vertices(vertices), shader(shader)
    {
        vao.Bind();
        vbo.Bind();
        vbo.SetData(vertices);
        
        vao.AddLayout<float>(3);
        vao.AddLayout<float>(2);
        vao.AddLayout<float>(3);
        vao.AddLayout<float>(4);
        vao.RegisterLayouts();
    }


    Mesh Mesh::FromObj(const std::string& filepath, const Shader& shader)
    {
        ObjData data = ObjParser::ParseFile(filepath);
        return Mesh(ObjParser::DataToVertices(data), shader, data.objectnames[0]);
    }

    void Mesh::AddTexture(Texture2D* texture)
    {
        textures.push_back(texture);
    }

    void Mesh::AddTextures(const std::vector<std::string>& paths)
    {
        for(unsigned int i = 0; i < paths.size(); i++)
            textures.push_back(new Texture2D(paths[i], i));
    }

    void Mesh::AddTextures(const std::vector<Texture2D*>& textures)
    {
        for(const auto texture : textures) this->textures.push_back(texture);
    }
    
    void Mesh::Draw()
    {
        // Logging what we are rendering
        if (first)
        {
            char multiple = textures.size() > 1 ? 's' : '\0';
            LOG_TRACE("[RENDERER] Rendering mesh \"{}\" with {} texture{}", name, textures.size(), multiple);
            first = false;
        }

        vao.Bind();
        for(const auto texture : textures) texture->Bind();
        shader.UseProgram();
        shader.SetUniformDataMat4f("model", transform.Matrix());
        shader.SetUniformData1i("albedoMap", textures[0]->GetSlot());
        //shader.SetUniformData1i("normalMap", textures[2]->GetSlot());
        glDrawArrays(GL_TRIANGLES, 0, (int)vertices.size());
    }

    // Getters
    const Galaxy::VertexArray& Mesh::GetVao() const
    {
        return vao;
    }

    const Galaxy::VertexBuffer& Mesh::GetVbo() const
    {
        return vbo;
    }

    const std::vector<Galaxy::Vertex>& Mesh::GetVertices() const
    {
        return vertices;
    }

}

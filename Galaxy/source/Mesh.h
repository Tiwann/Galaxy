#pragma once
#include <string>
#include <vector>

#include "Shader.h"
#include "Texture2D.h"
#include "Vertex.h"
#include "VertexArray.h"


namespace Galaxy
{
    class Mesh
    {
    protected:
        VertexArray vao;
        VertexBuffer vbo;
        std::vector<Vertex> vertices;
        Shader shader;
        std::vector<Texture2D*> textures;
        std::string name;
        bool first = true;
    public:
        Mesh(const std::vector<Vertex>& vertices, const Shader& shader, const std::string& name);
        
        static Mesh FromObj(const std::string& filepath, const Shader& shader);
        void AddTexture(Texture2D* texture);
        void AddTextures(const std::vector<std::string>& paths);
        void AddTextures(const std::vector<Texture2D*>& textures);
        void Draw();

        // Getters
        const VertexArray& GetVao() const;
        const VertexBuffer& GetVbo() const;
        const std::vector<Vertex>& GetVertices() const;
        const std::vector<Texture2D*> GetTextures() const { return textures; }
        const std::string& GetName() const { return name; }
    };
}


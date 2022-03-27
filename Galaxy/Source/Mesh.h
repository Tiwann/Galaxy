#pragma once
#include <string>
#include <vector>

#include "Shader.h"
#include "Texture2D.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "SceneObject.h"

namespace Galaxy
{
    class Mesh : public SceneObject
    {
    private:
        bool first = true;
    protected:
        VertexArray vao;
        VertexBuffer vbo;
        std::vector<Vertex> vertices;
        Shader shader;
        std::vector<Texture2D*> textures;

        
    public:
        Mesh(const std::vector<Vertex>& vertices, const Shader& shader, const std::string& in_name = "NewMeshObject");
        
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

    };
}


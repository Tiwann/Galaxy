#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "Log/Log.h"
#include "Window/Window.h"
#include "Renderer/Vertex.h"
#include "Shader/Shader.h"
#include "Renderer/VertexArray/VertexArray.h"
#include "Renderer/VertexBuffer/VertexBuffer.h"
#include "Renderer/IndexBuffer/IndexBuffer.h"
#include "Utils/ObjParser/ObjParser.h"
#include "stb/stb_image.h"

#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 1

int main() {
    Galaxy::Log::Init();
    
    Galaxy::LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR);

    Galaxy::Window* window = Galaxy::Window::Create("Galaxy Renderer", 600, 600, false, 16);

    if (!window->GetWindow()) {
        Galaxy::LOG_ERROR("Failed to create a window.");
        return -1;
    }

    window->MakeContextCurrent();

    if (glewInit() != GLEW_OK) {
        Galaxy::LOG_ERROR("Couldn't initalize GLEW.");
        return -1;
    }

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_FRAMEBUFFER_SRGB);

    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
    Galaxy::LOG_TRACE("Using OpenGL: {}\n", glGetString(GL_VERSION));

    const Galaxy::Vertices vertices = {
        {
            .position   = glm::vec3(-0.5f, -0.5f, 0.0f),
            .texCoord   = glm::vec2(0.0f, 0.0f),
            .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
            .color      = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
        },
        {
            .position   = glm::vec3(-0.5f, 0.5f, 0.0f),
            .texCoord   = glm::vec2(0.0f, 1.0f),
            .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
            .color      = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
        },
        {
            .position   = glm::vec3(0.5f, 0.5f, 0.0f),
            .texCoord   = glm::vec2(1.0f, 1.0f),
            .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
            .color      = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
        },
        {
            .position = glm::vec3(0.5f, -0.5f, 0.0f),
            .texCoord = glm::vec2(1.0f, 0.0f),
            .normal = glm::vec3(0.0f, 0.0f, 0.0f),
            .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
        }
    };

    unsigned int indices[] = { 0, 2, 1, 0, 3, 2 };

    Galaxy::Shader* shader = Galaxy::Shader::Create("Main/Main.vert", "Main/Main.frag");
    shader->Compile();
    shader->Link();
    shader->Delete();

    // Create vao, vbo, ibo
    Galaxy::VertexArray* vao    = Galaxy::VertexArray::Create();
    Galaxy::VertexBuffer* vbo   = Galaxy::VertexBuffer::Create();
    Galaxy::IndexBuffer* ibo    = Galaxy::IndexBuffer::Create();

    vao->Bind();

    vbo->Bind();
    vbo->SetData(vertices);

    ibo->Bind();
    ibo->SetData(sizeof(indices), indices);

    // Position Attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);

    // TexCoord Attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));

    // Normal attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(5 * sizeof(float)));

    // Color Attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(8 * sizeof(float)));

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    const unsigned char* bytes = stbi_load("Assets/Textures/cap.png", &width, &height, &channels, 0);
    
    uint32_t texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE0, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    uint32_t tex0uni = glGetUniformLocation(shader->GetProgram(), "tex0");
    shader->UseProgram();
    glUniform1i(tex0uni, 0);

    while (!window->ShouldClose()) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->UseProgram();      
        

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
        //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        // Swap back and front buffers
        window->SwapBuffers();
        glfwPollEvents();
    }


    
    glfwTerminate();
    return 0;
}
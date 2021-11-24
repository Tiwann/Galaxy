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

#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 1

int main() {
    Galaxy::Log::Init();
    
    Galaxy::LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR);

    if (!glfwInit()) {
        Galaxy::LOG_ERROR("Couldn't initalize GLFW.");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Galaxy::Window* window = Galaxy::Window::Create("Galaxy Renderer", 800, 600, false, 16);

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
    glEnable(GL_FRAMEBUFFER_SRGB);

    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
    Galaxy::LOG_TRACE("Using OpenGL: {}\n", glGetString(GL_VERSION));

    const Galaxy::Vertex verticies[] = {
        {
            .position   = glm::vec3(-0.5f, -0.5f, 0.0f),
            .color      = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
            .texCoord   = glm::vec2(0.0f, 0.0f)
        },
        {
            .position   = glm::vec3(0.0f, 0.5f, 0.0f),
            .color      = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
            .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
            .texCoord   = glm::vec2(0.0f, 0.0f)
        },
        {
            .position   = glm::vec3(0.5f, -0.5f, 0.0f),
            .color      = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
            .texCoord   = glm::vec2(0.0f, 0.0f)
        }
    };

    unsigned int indices[] = { 0, 1, 2 };

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
    vbo->SetData(sizeof(verticies), verticies);

    ibo->Bind();
    ibo->SetData(sizeof(indices), indices);

    auto obj = Galaxy::ObjParser::ParseFile("Assets/Models/sphere.obj");

    // Position Attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)0);

    // Color Attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(3 * sizeof(float)));

    // Normal attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(7 * sizeof(float)));

    // TexCoord Attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void*)(10 * sizeof(float)));

    vao->Unbind();


    while (!window->ShouldClose()) 
    {
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao->Bind();
        shader->UseProgram();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        // Swap back and front buffers
        window->SwapBuffers();
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
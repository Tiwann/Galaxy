#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "Log/Log.h"
#include "Window/Window.h"
#include "Renderer/Vertex.h"
#include "Shader/Shader.h"

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
    Galaxy::LOG_TRACE("Using OpenGL: {}", glGetString(GL_VERSION));

    const Galaxy::Vertex verticies[] = {
        {
            .position = glm::vec3(-0.5f, -0.5f, 0.0f),
            .color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
            .normal = glm::vec3(0.0f, 0.0f, 0.0f),
            .texCoord = glm::vec2(0.0f, 0.0f)
        },
        {
            .position = glm::vec3(0.0f, 0.5f, 0.0f),
            .color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
            .normal = glm::vec3(0.0f, 0.0f, 0.0f),
            .texCoord = glm::vec2(0.0f, 0.0f)
        },
        {
            .position = glm::vec3(0.5f, -0.5f, 0.0f),
            .color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
            .normal = glm::vec3(0.0f, 0.0f, 0.0f),
            .texCoord = glm::vec2(0.0f, 0.0f)
        }
    };

    unsigned int indices[] = { 0, 1, 2 };

    // Create vao, vbo, ibo
    unsigned int vao;
    unsigned int vbo;
    unsigned int ibo;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    glBindVertexArray(vao);

    Galaxy::Shader* shader = new Galaxy::Shader("Main/Main.vert", "Main/Main.frag");
    shader->Compile();
    shader->Link();
    shader->Delete();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

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


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    while (!window->ShouldClose()) 
    {
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader->UseProgram();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        // Swap back and front buffers
        window->SwapBuffers();
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
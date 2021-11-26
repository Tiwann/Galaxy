#include <GL/glew.h>
#include <glfw/glfw3.h>
#include "Log/Log.h"
#include "Window/Window.h"
#include "Shader/Shader.h"
#include "Renderer/Vertex.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Utils/ObjParser/ObjParser.h"
#include "stb/stb_image.h"
#include "Texture/Texture2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    window->SetVSyncEnabled(true);

    if (glewInit() != GLEW_OK) {
        Galaxy::LOG_ERROR("Couldn't initalize GLEW.");
        return -1;
    }

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);

    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
    Galaxy::LOG_TRACE("Using OpenGL: {}\n", glGetString(GL_VERSION));

    //const Galaxy::Vertices vertices = {
    //    {
    //        .position   = glm::vec3(-0.5f, -0.5f, 0.0f),
    //        .texCoord   = glm::vec2(0.0f, 0.0f),
    //        .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
    //        .color      = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
    //    },
    //    {
    //        .position   = glm::vec3(-0.5f, 0.5f, 0.0f),
    //        .texCoord   = glm::vec2(0.0f, 1.0f),
    //        .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
    //        .color      = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
    //    },
    //    {
    //        .position   = glm::vec3(0.5f, 0.5f, 0.0f),
    //        .texCoord   = glm::vec2(1.0f, 1.0f),
    //        .normal     = glm::vec3(0.0f, 0.0f, 0.0f),
    //        .color      = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
    //    },
    //    {
    //        .position = glm::vec3(0.5f, -0.5f, 0.0f),
    //        .texCoord = glm::vec2(1.0f, 0.0f),
    //        .normal = glm::vec3(0.0f, 0.0f, 0.0f),
    //        .color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
    //    }
    //};
    //
    //unsigned int indices[] = { 0, 2, 1, 0, 3, 2 };

    Galaxy::Vertices cube = Galaxy::ObjParser::ParseFileToVertices("Assets/Models/superleaf.obj");
    Galaxy::Shader* shader = Galaxy::Shader::Create("Main/Main.vert", "Main/Main.frag");
    shader->Compile();
    shader->Link();
    shader->Delete();

    Galaxy::Texture2D* texture = Galaxy::Texture2D::Create("Assets/Textures/superleaf.png", { GL_TEXTURE0, GL_RGBA, GL_NEAREST, GL_REPEAT });
    texture->SetUniformData(shader, "tex0", 0);

    // Create vao, vbo, ibo
    Galaxy::VertexArray* vao    = Galaxy::VertexArray::Create();
    Galaxy::VertexBuffer* vbo   = Galaxy::VertexBuffer::Create();
    Galaxy::IndexBuffer* ibo    = Galaxy::IndexBuffer::Create();

    vao->Bind();

    vbo->Bind();
    vbo->SetData(cube);

    //ibo->Bind();
    //ibo->SetData(sizeof(indices), indices);

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



    
    float rotation = 0.0f;
    double oldTime = glfwGetTime();
    while (!window->ShouldClose()) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        double currentTime = glfwGetTime();
        if (currentTime - oldTime >= (1 / 60))
        {
            rotation += 0.5f;
            oldTime = currentTime;
        }


        shader->UseProgram();      
        texture->Bind();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0, -5.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)(window->GetWidth() / window->GetHeight()), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader->GetProgram(), "model");
        glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(model));

        int viewlLoc = glGetUniformLocation(shader->GetProgram(), "view");
        glUniformMatrix4fv(viewlLoc, 1, false, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader->GetProgram(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, false, glm::value_ptr(projection));

        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, (int)cube.size());
        // Swap back and front buffers
        window->SwapBuffers();
        glfwPollEvents();
    }
    

    
    glfwTerminate();
    return 0;
}
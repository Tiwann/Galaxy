#include <GL/glew.h>
#include "Log.h"
#include "Window.h"
#include "Shader.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ObjParser.h"
#include "Texture2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 1

int main() {
    Galaxy::Log::Init();
    Galaxy::LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR);

    // Creating the window
    Galaxy::Window window("Galaxy Renderer", 600, 600, false, 16);
    if (!window.Check()) return -1;

    // Logging versions
    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
    Galaxy::LOG_TRACE("Using OpenGL: {}\n", glGetString(GL_VERSION));

    // Importing a model from obj file
    using VertexArray = std::vector<Galaxy::Vertex>;
    VertexArray cube = Galaxy::ObjParser::ParseFileToVertices("Assets/Models/superleaf.obj");

    // Creating a shader to use 
    Galaxy::Shader shader("Main/Main.vert", "Main/Main.frag");
    // Compiling the shader
    shader.Compile();
    shader.Link();
    shader.Delete();

    // Creating a Texture2D 
    Galaxy::Texture2D texture("Assets/Textures/superleaf.png", GL_TEXTURE0, Galaxy::TextureParams::Default);
    // Setting uniform data in the shader
    texture.SetUniformData(shader, "albedo", 0);

    // Creating vao, vbo, ibo for rendering 
    Galaxy::VertexArray vao; 
    Galaxy::VertexBuffer vbo;
    Galaxy::IndexBuffer ibo;

    vao.Bind();     
    vbo.Bind();
    vbo.SetData(cube);


    //TODO:
    // Attributes / Layout abstraction
    // May create a BufferLayout class in which we can push data in, then fill those gl func programatically
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
    while (!window.ShouldClose()) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        double currentTime = glfwGetTime();
        if (currentTime - oldTime >= (1 / 60))
        {
            rotation += 0.5f;
            oldTime = currentTime;
        }


        shader.UseProgram();      
        texture.Bind();

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0, -5.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)(window.GetWidth() / window.GetHeight()), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(shader.GetProgram(), "model");
        glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(model));

        int viewlLoc = glGetUniformLocation(shader.GetProgram(), "view");
        glUniformMatrix4fv(viewlLoc, 1, false, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader.GetProgram(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, false, glm::value_ptr(projection));

        //glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, (int)cube.size());
        // Swap back and front buffers
        window.SwapBuffers();
        glfwPollEvents();
    }
    
    Galaxy::LOG_TRACE("Closing application...");
    glfwTerminate();
    return 0;
}
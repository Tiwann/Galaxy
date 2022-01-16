// ReSharper disable All
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
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
#include "Vector3.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"

#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 2

int main() {
    Galaxy::Log::Init();
    Galaxy::LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR);

    // Creating the window
    Galaxy::Window window("Galaxy Renderer", 1280, 720, false, 16);
    if (!window.Check()) return -1;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // Logging versions
    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
    Galaxy::LOG_TRACE("Using ImGUI version {}", IMGUI_VERSION);
    Galaxy::LOG_TRACE("Using OpenGL: {}", glGetString(GL_VERSION));
    Galaxy::LOG_TRACE("Renderer: {}\n", glGetString(GL_RENDERER));

    



    // Creating a shader to use 
    Galaxy::Shader shader("Main/Main.vert", "Main/Main.frag");
    // Compiling the shader
    shader.Compile();
    shader.Link();
    shader.Delete();

    
    Galaxy::Mesh mario = Galaxy::Mesh::FromObj("Assets/Characters/Mario/Mario.obj", shader);
    Galaxy::Mesh leaf = Galaxy::Mesh::FromObj("Assets/Models/superleaf.obj", shader);

    
    mario.AddTexture(new Galaxy::Texture2D("Assets/Characters/Mario/images/mario_tex.png", 0));
    leaf.AddTexture(new Galaxy::Texture2D("Assets/Textures/superleaf.png", 0));
    
    float orthoScale = 3.0f;

    Galaxy::Vector3 cameraPos = Galaxy::Vector3(0.0f, 0.0f, -1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), cameraPos);
    glm::mat4 projection = glm::ortho(-16.0f * orthoScale, 16.0f * orthoScale, -9.0f * orthoScale,9.0f * orthoScale, 0.00001f, 10000000.0f);

    Galaxy::Vector3 pos = Galaxy::Vector3(-1.0f, 0.0f, 0.0f);
    Galaxy::Vector3 pos2 = Galaxy::Vector3(1.0f, 0.0f, 0.0f);

    float rotation = 0.0f;
    double oldTime = glfwGetTime();
    while (!window.ShouldClose()) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        double currentTime = glfwGetTime();
        if (currentTime - oldTime >= (1 / 60))
        {
            rotation += 0.5f;
            oldTime = currentTime;
        }
        
        projection = glm::ortho(
            -16.0f / orthoScale,
            16.0f / orthoScale,
            -9.0f / orthoScale,
            9.0f / orthoScale,
            0.00001f,
            10000.0f);

        view = glm::translate(glm::mat4(1.0f), cameraPos);
        // Make the model rotate
        model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(1.0f));

        shader.UseProgram();
        // Transfer our matrices to the shader
        shader.SetUniformDataMat4f("model", model);
        shader.SetUniformDataMat4f("view", view);
        shader.SetUniformDataMat4f("projection", projection);


        
        shader.SetUniformData1i("albedo", mario.GetTextures()[0]->GetSlot());
        mario.Draw();

        

        model = glm::mat4(1.0f);
        model = glm::translate(model, pos2);
        model = glm::rotate(model, glm::radians(rotation), Galaxy::Vector3::Up);
        model = glm::scale(model, glm::vec3(1.0f));

        shader.SetUniformDataMat4f("model", model);
        shader.SetUniformData1i("albedo", leaf.GetTextures()[0]->GetSlot());
        leaf.Draw();


        ImGui::Begin("Galaxy Panel");
        ImGui::DragFloat3("Mario Position", (float*)&pos, 0.001f);
        ImGui::DragFloat3("Leaf Position", (float*)&pos2, 0.001f);
        ImGui::DragFloat3("Camera Position", (float*)&cameraPos, 0.001f);
        ImGui::DragFloat("Ortho", &orthoScale, 0.001f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap back and front buffers
        window.SwapBuffers();
        window.PollEvents();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    Galaxy::LOG_TRACE("Closing application...");
    glfwTerminate();
    return 0;
}
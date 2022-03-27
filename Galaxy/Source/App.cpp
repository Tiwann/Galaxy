#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Log.h"
#include "Window.h"
#include "Shader.h"
#include "Vertex.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ObjParser.h"
#include "Texture2D.h"
#include "Camera.h"

#include "Mesh.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Scene.h"
#include "DetailPanel.h"
#include "ImGuiStyle.h"
#include "DirectionalLight.h"
#include "tinyfiledialogs.h"

#include "Application.h"


int main(const int argc, const char** argv) {

    Galaxy::Application& App = Galaxy::Application::Get();
    App.Run();
    
    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    Galaxy::SetGuiStyleGalaxy();

    ImGui_ImplGlfw_InitForOpenGL(App.GetMainWindow()->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");


    // Logging versions
    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLAD version {}", GLAD_GL_VERSION_4_6);
    Galaxy::LOG_TRACE("Using ImGUI version {}", IMGUI_VERSION);
    Galaxy::LOG_TRACE("Using OpenGL: {}", glGetString(GL_VERSION));
    Galaxy::LOG_TRACE("Using Graphics Card: {}\n", glGetString(GL_RENDERER));


    // Ready to create scene.
    Galaxy::Scene& scene = Galaxy::Scene::Get();


    // Creating a shader to use 
    Galaxy::Shader shader("Main/Main.vert", "Main/Main.frag");
    // Compiling the shader
    shader.Compile();
    shader.Link();
    shader.Delete();

    // Create a mesh and add it to the scene hierarchy
    Galaxy::Mesh shell = Galaxy::Mesh::FromObj("Assets/Characters/Mario/Mario.obj", shader);
    shell.AddTexture(new Galaxy::Texture2D("Assets/Characters/Mario/mario_tex.png", 0));
    shell.GetTransform().Translate(glm::vec3(0.0f, 0.0f, -3.0f));


    Galaxy::Camera camera(Galaxy::CameraMode::PERSP, (float)App.GetMainWindow()->GetWidth(), (float)App.GetMainWindow()->GetHeight(), 0.01f, 100.0f);
    Galaxy::DirectionalLight light;
    light.GetTransform().Translate(glm::vec3(-30.0f, 0.0f, 20.0f));

    

    while (!App.GetMainWindow()->ShouldClose())
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        
        light.SetDirection(shell.GetTransform().position - light.GetTransform().position);

        shader.UseProgram();
        // Transfer our matrices to the shader
        shader.SetUniformDataMat4f("view", camera.GetViewMatrix());
        shader.SetUniformDataMat4f("projection", camera.GetProjectionMatrix());

        //Set light data to shader
        shader.SetUniformData3f("lightPos", light.GetTransform().position);
        shader.SetUniformData4f("lightColor", light.GetColor());
        shader.SetUniformData3f("cameraPos", camera.GetTransform().position);

        shell.GetTransform().Rotate(glm::vec3(0.0f, 0.4f, 0.0f));
        shell.Draw();

        Galaxy::Scene::Get().OnGuiRender(ImGui::GetIO());
        Galaxy::DetailPanel::Get().OnGuiRender(ImGui::GetIO());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap back and front buffers
        App.GetMainWindow()->SwapBuffers();
        App.GetMainWindow()->PollEvents();
    }


    Galaxy::LOG_TRACE("[IMGUI] Shutdown ImGui...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    Galaxy::LOG_TRACE("[APP] Closing application...");
    glfwTerminate();
    return 0;
}

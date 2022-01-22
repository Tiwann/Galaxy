#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>

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

#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 2

static void Draw()
{

}


int main() {
    Galaxy::Log::Init();
    Galaxy::LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR);

    // Creating the window
    Galaxy::Window window("Galaxy Renderer", 1280, 720, true, 16);
    if (!window.Check()) return -1;
    
    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    Galaxy::SetGuiStyleGalaxy();
    
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
    

    // Logging versions
    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
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
    Galaxy::Mesh mario = Galaxy::Mesh::FromObj("Assets/Characters/Mario/Mario.obj", shader);
    mario.AddTexture(new Galaxy::Texture2D("Assets/Characters/Mario/mario_tex.png", 0));
    mario.GetTransform().Translate(glm::vec3(0.0f, 0.0f, -3.0f));

    Galaxy::Mesh minecraft = Galaxy::Mesh::FromObj("Assets/Models/cube.obj", shader);
    minecraft.AddTexture(new Galaxy::Texture2D("Assets/Textures/minecraft_sand.png", 0));
    minecraft.GetTransform().Translate(glm::vec3(2.0f, 0.0f, -3.0f));
    minecraft.Rename("Cube");

    using enum Galaxy::CameraMode;
    Galaxy::Camera camera(PERSP, (float)window.GetWidth(), (float)window.GetHeight(), 0.01f, 100.0f);

    

   
    while (!window.ShouldClose()) 
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        shader.UseProgram();
        // Transfer our matrices to the shader
        shader.SetUniformDataMat4f("view", camera.GetViewMatrix());
        shader.SetUniformDataMat4f("projection", camera.GetProjectionMatrix());

        // Set transform data to shader and render mario
        shader.SetUniformDataMat4f("model", mario.GetTransform().GetTransformMatrix());
        shader.SetUniformData1i("albedo", mario.GetTextures()[0]->GetSlot());
        mario.Draw();

        // Set transform data to shader and render mincraft cube
        shader.SetUniformDataMat4f("model", minecraft.GetTransform().GetTransformMatrix());
        shader.SetUniformData1i("albedo", minecraft.GetTextures()[0]->GetSlot());
        minecraft.Draw();


        Galaxy::Scene::Get().OnGuiRender(ImGui::GetIO());
        Galaxy::DetailPanel::Get().OnGuiRender(ImGui::GetIO());


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap back and front buffers
        window.SwapBuffers();
        window.PollEvents();
    }
    

    Galaxy::LOG_TRACE("[IMGUI] Shutdown ImGui...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    Galaxy::LOG_TRACE("[APP] Closing application...");
    glfwTerminate();
    return 0;
}

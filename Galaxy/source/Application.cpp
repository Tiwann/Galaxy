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

#define GALAXY_VERSION_MAJOR 0
#define GALAXY_VERSION_MINOR 2

int main() {
    Galaxy::Log::Init();
    Galaxy::LOG_TRACE("Welcome to Galaxy Renderer version {}.{}!", GALAXY_VERSION_MAJOR, GALAXY_VERSION_MINOR);

    // Creating the window
    Galaxy::Window window("Galaxy Renderer", 1280, 720, false, 16);
    if (!window.Check()) return -1;
    
    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto io = ImGui::GetIO();
    ImGui::StyleColorsLight();
    ImGui_ImplGlfw_InitForOpenGL(window.GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    // Logging versions
    Galaxy::LOG_TRACE("Using GLFW version {}.{}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR);
    Galaxy::LOG_TRACE("Using GLEW version {}.{}.{}", GLEW_VERSION_MAJOR, GLEW_VERSION_MINOR, GLEW_VERSION_MICRO);
    Galaxy::LOG_TRACE("Using ImGUI version {}", IMGUI_VERSION);
    Galaxy::LOG_TRACE("Using OpenGL: {}", glGetString(GL_VERSION));
    Galaxy::LOG_TRACE("Using Graphics Card: {}\n", glGetString(GL_RENDERER));
    

    // Ready to create scene.
    auto scene = Galaxy::Scene::Get();
    scene.Init();




    // Creating a shader to use 
    Galaxy::Shader shader("Main/Main.vert", "Main/Main.frag");
    // Compiling the shader
    shader.Compile();
    shader.Link();
    shader.Delete();

    Galaxy::Mesh mario = Galaxy::Mesh::FromObj("Assets/Characters/Mario/Mario.obj", shader);
    mario.AddTexture(new Galaxy::Texture2D("Assets/Characters/Mario/mario_tex.png", 0));
    mario.GetTransform().Translate(glm::vec3(0.0f, 0.0f, -3.0f));
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
        shader.SetUniformDataMat4f("model", mario.GetTransform().GetTransformMatrix(false));
        shader.SetUniformDataMat4f("view", camera.GetTransform().GetTransformMatrix(true));
        shader.SetUniformDataMat4f("projection", camera.GetProjectionMatrix());

        shader.SetUniformData1i("albedo", mario.GetTextures()[0]->GetSlot());
        mario.Draw();
  

        ImGui::Begin("Galaxy Panel");
        const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen |
                                                 ImGuiTreeNodeFlags_Framed |
                                                 ImGuiTreeNodeFlags_SpanAvailWidth |
                                                 ImGuiTreeNodeFlags_AllowItemOverlap |
                                                 ImGuiTreeNodeFlags_FramePadding;
        

        if (ImGui::TreeNodeEx("Mario", treeNodeFlags))
        {
            if (ImGui::TreeNodeEx("Transform", treeNodeFlags))
            {
                
                ImGui::DragFloat3("Position", glm::value_ptr(mario.GetPosition()), 0.01f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(mario.GetRotation()), 0.01f);
                ImGui::DragFloat3("Scale", glm::value_ptr(mario.GetScale()), 0.01f);
                ImGui::TreePop();
            }        
            ImGui::TreePop();
        }
        
        if (ImGui::TreeNodeEx("Camera", treeNodeFlags))
        {

            if (ImGui::TreeNodeEx("Transform", treeNodeFlags))
            {
                ImGui::DragFloat3("Position", glm::value_ptr(camera.GetPosition()), 0.01f);
                ImGui::DragFloat3("Rotation", glm::value_ptr(camera.GetRotation()), 0.01f);
                ImGui::DragFloat3("Scale", glm::value_ptr(camera.GetScale()), 0.01f);
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Parameters", treeNodeFlags))
            {         
                const char* items[]{ "Orthographic", "Perspective" };
                static int selectedItem = (int)camera.GetMode();
                ImGui::Combo("Camera Mode", &selectedItem, items, IM_ARRAYSIZE(items));
                switch (selectedItem) {
                case 0:
                    camera.SetMode(Galaxy::CameraMode::ORTHO);
                    ImGui::DragFloat("Orthographic Scale", &camera.GetOrthoScale(), 0.1f);
                    break;
                case 1:
                    camera.SetMode(Galaxy::CameraMode::PERSP);
                    ImGui::DragFloat("Field Of View", &camera.GetFieldOfView(), 0.1f, 0.0f, 0.0f, "%.1f Degrees");
                    break;
                }
                ImGui::TreePop();
            }

            
            ImGui::TreePop();
        }

        
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap back and front buffers
        window.SwapBuffers();
        window.PollEvents();
    }
    

    Galaxy::LOG_TRACE("Shutdown ImGui...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    Galaxy::LOG_TRACE("Closing application...");
    glfwTerminate();
    return 0;
}